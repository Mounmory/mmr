#include "util/Clogger.h"
#include "util/UtilFunc.h"
#include <stdarg.h>

#include <iomanip> //std::setfillͷ�ļ�


#ifdef OS_WIN
#include <corecrt_io.h>	//_accessͷ�ļ�
#include <windows.h>
#elif defined OS_LINUX
#include <sys/stat.h>  //�½��ļ���ͷ�ļ�
#include <sys/types.h> //�½��ļ���ͷ�ļ�
#include <unistd.h>
#endif

#define MAX_FILE_SIZE 4*1024*1024
//#define MAX_FILE_SIZE 100

#define LOG_BY_LEVEL(logLevel)\
static char* strBufPtr = nullptr;\
std::lock_guard<std::mutex> guard(m_mutWrite);\
if (LogCheck(logLevel) == false)\
return;\
va_list arglist;\
va_start(arglist, format);\
int strLen = vsnprintf(m_pBuf, m_lBufLen, format, arglist);\
if (strLen > m_lBufLen && strLen < m_lBigBufLen)\
{\
	vsnprintf(m_pBigBuf, m_lBigBufLen, format, arglist);\
	strBufPtr = &m_pBigBuf[0];\
}\
else\
{\
	strBufPtr = &m_pBuf[0];\
}\
va_end(arglist);\
auto now = std::chrono::system_clock::now();\
auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;\
std::time_t current_time = std::chrono::system_clock::to_time_t(now);\
std::tm* time_info = std::localtime(&current_time);\
m_logStream << "[" << std::this_thread::get_id() << "]"\
<< (time_info->tm_year + 1900) << "-" << std::setfill('0') << std::setw(2) << (time_info->tm_mon + 1) << "-" << std::setfill('0') << std::setw(2) << time_info->tm_mday\
<< " " << std::setfill('0') << std::setw(2) << time_info->tm_hour << ":" << std::setfill('0') << std::setw(2) << time_info->tm_min << ":"\
<< std::setfill('0') << std::setw(2) << time_info->tm_sec << "." << std::setfill('0') << std::setw(3) << now_ms\
<< strBufPtr << std::endl


mmrUtil::CLogger::CLogger()
	: m_LogLevel(emLogLevel::LOG_DEBUG)
	, m_lBufLen(1024)
	, m_lBigBufLen(4096)
	, m_pBuf(new char[m_lBufLen])
	, m_pBigBuf(new char[m_lBigBufLen])
	, m_fileNum(10)
	, m_fileSize(MAX_FILE_SIZE)
{

}

mmrUtil::CLogger::~CLogger()
{
	stop();
	delete[] m_pBuf;
	delete[] m_pBigBuf;
}

mmrUtil::CLogger* mmrUtil::CLogger::getLogger()
{
	static CLogger* loggerInstance = new CLogger;
	return loggerInstance;
}

bool mmrUtil::CLogger::setFileMaxNum(uint32_t fileNum)
{
	if (m_logStream.is_open()) 
		return false;

	m_fileNum = fileNum;
	return true;
}

bool mmrUtil::CLogger::setFileMaxSize(uint64_t fileSize)
{
	if (m_logStream.is_open())
		return false;

	m_fileSize = fileSize;
	return true;
}

bool mmrUtil::CLogger::setLogLevel(emLogLevel logLevel)
{
	if (m_logStream.is_open())
		return false;

	m_LogLevel = logLevel;
	return true;
}

bool mmrUtil::CLogger::init(const std::string& strPath, const std::string& strName)
{
	m_strLogDir = strPath;
	m_strLogName = strName;
	m_strFilePath = m_strLogDir + m_strLogName + ".log";
#ifdef OS_WIN
	if (_access(m_strLogDir.c_str(), 0) == -1)//������ݿ��ļ��в����ڣ��򴴽�
	{
		if (CreateDirectory(m_strLogDir.c_str(), 0) == false)
		{
			m_LogLevel = emLogLevel::LOG_OFF;//�����ļ���ʧ�ܣ��������־
			std::cerr <<"[" << __FUNCTION__ << "]["<< __LINE__ << "Create directory " << m_strLogDir.c_str() << "failed!" << std::endl;
			return false;
		}
	}
#elif defined OS_LINUX
	if (access(m_strLogDir.c_str(), 0) != F_OK) //����ļ����Ƿ���ڣ��������򴴽�
	{
		mkdir(m_strLogDir.c_str(), S_IRWXO); //�����˶���Ȩ�޶�д

		if (access(m_strLogDir.c_str(), 0) != F_OK)
		{
			m_LogLevel = emLogLevel::LOG_OFF;//�����ļ���ʧ�ܣ��������־
			std::cerr << "[" << __FUNCTION__ << "][" << __LINE__ << "Create directory " << m_strLogDir.c_str() << "failed!" << std::endl;
			return false;
		}
	}
#endif
	//�������ļ����ò���

	return true;
}

bool mmrUtil::CLogger::start()
{
	//m_pBufDeal = std::make_unique<CBigBuff>(m_ulBigBufSize);

	m_pBufWrite = std::make_unique<CBigBuff>(m_ulBigBufSize);

	for (uint16_t i = 0; i < m_usBufEmptySize; ++i) 
	{
		m_queBufsEmpty.push(std::make_unique<CBigBuff>(m_ulBigBufSize));
	}


	if (m_strLogDir.empty() || m_strLogName.empty())
	{
		std::string logDir, logName;
		getAppPathAndName(logDir, logName);
		logDir += "log/";
		if (!init(logDir, logName)) 
		{
			return false;
		}
	}

	if (!m_logStream.is_open())
	{
		m_logStream.open(m_strFilePath.c_str(), std::ios::app);
		if (m_logStream.fail())
		{
			std::cerr << "[" << __FUNCTION__ << "][" << __LINE__ << "open file " << m_strFilePath.c_str() << "failed!" << std::endl;
			return false;
		}
		m_logStream.seekp(0, std::ios::end);
	}

	//���������߳�
	m_bRunning.store(true, std::memory_order_relaxed);
	m_threadDeal = std::make_unique<std::thread>(&CLogger::dealThread, this);

	LOG_FORCE("----------------- start -----------------");
	return true;
}

void mmrUtil::CLogger::stop()
{
	//ͣ���߳�
	if (true == m_bRunning)
	{
		m_bRunning.store(false, std::memory_order_relaxed);//�˳��߳�
		m_cv.notify_all();
		if (m_threadDeal->joinable())
		{
			m_threadDeal->join();//�ȴ��߳̽���
		}
	}

	if (m_logStream.is_open())
	{
		m_logStream.close();
	}
}

void mmrUtil::CLogger::LogForce(const char *format, ...)
{
	//LOG_BY_LEVEL(emLogLevel::LOG_FORCE, O);
	if (m_LogLevel < emLogLevel::LOG_FORCE)
	{
		return;
	}
	auto now = std::chrono::system_clock::now();
	auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;
	std::time_t current_time = std::chrono::system_clock::to_time_t(now);
	std::tm* time_info = std::localtime(&current_time);

	std::unique_lock<std::mutex> lock(m_mutWrite);
	if (time_info->tm_sec != m_lastTime.tm_sec //�ɵ͵��߱Ƚ�
		|| time_info->tm_min != m_lastTime.tm_min
		|| time_info->tm_hour != m_lastTime.tm_hour
		|| time_info->tm_mday != m_lastTime.tm_mday
		|| time_info->tm_mon != m_lastTime.tm_mon
		|| time_info->tm_year != m_lastTime.tm_year)
	{
		m_lastTime.tm_sec = time_info->tm_sec; 
		m_lastTime.tm_min = time_info->tm_min;
		m_lastTime.tm_hour = time_info->tm_hour;
		m_lastTime.tm_mday = time_info->tm_mday;
		m_lastTime.tm_mon = time_info->tm_mon;
		m_lastTime.tm_year = time_info->tm_year;

		snprintf(m_szLastTime, sizeof(m_szLastTime), "%04d-%02d-%02d %02d:%02d:%02d ",
			m_lastTime.tm_year + 1900, m_lastTime.tm_mon + 1, m_lastTime.tm_mday,
			m_lastTime.tm_hour, m_lastTime.tm_min, m_lastTime.tm_sec);
	}
	//д��ms


	if (m_pBufWrite->getTryAvailid() <= strlen(m_szLastTime))//�ַ����Ȳ�����
	{
		updateBufWrite();
		m_cv.notify_all();
	}

	m_pBufWrite->tryWrite(m_szLastTime, strlen(m_szLastTime));

	va_list arglist;
	va_start(arglist, format);
	size_t weakAvilid = m_pBufWrite->getTryAvailid();
	int strLen = vsnprintf(m_pBufWrite->getTryCurrent(), weakAvilid, format, arglist);
	if (strLen > weakAvilid)
	{
		m_pBufWrite->clearTry();

		updateBufWrite();

		m_cv.notify_all();

		m_pBufWrite->tryWrite(m_szLastTime, strlen(m_szLastTime));
		//ע�⣺�������ݵ�availid����С��strLen�������º���addTryIncrease���ȴ��󣬵��½����峤�������ϴ󣬼��������ܳ��֣�������Ҳ��������ж�
		vsnprintf(m_pBufWrite->getTryCurrent(), m_pBufWrite->getTryAvailid(), format, arglist);
	}
	m_pBufWrite->addTryIncrease(strLen);
	m_pBufWrite->doneTry();
	va_end(arglist);
}

void mmrUtil::CLogger::LogFatal(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_FATAL);
}

void mmrUtil::CLogger::LogError(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_ERROR);
}

void mmrUtil::CLogger::LogWarn(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_WARN);
}

void mmrUtil::CLogger::LogInfo(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_INFO);
}

void mmrUtil::CLogger::LogDebug(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_DEBUG);
}

bool mmrUtil::CLogger::LogCheck(emLogLevel level)
{
	// check log level
	if (m_LogLevel < level)
	{
		return false;
	}

	if (!m_logStream.is_open() || !m_logStream.seekp(0, std::ios::end))//���û�д�
	{
		m_LogLevel = emLogLevel::LOG_OFF;
		std::cerr << "log file open failed!" << std::endl;
		return false;
	}

	if (m_logStream.tellp() > m_fileSize)//�ļ���������ļ���С
	{
		//�޸��ļ�����
		m_logStream.close();

		std::string strOldName; //������
		std::string strNewName; //������
		int32_t nLogNumIndex = m_fileNum;
		strNewName = m_strFilePath + "." + std::to_string(nLogNumIndex); //�����ŵ���־
#ifdef OS_WIN
		if (_access(strNewName.c_str(), 0) != -1)
		{
			remove(strNewName.c_str()); //ɾ��
		}
		while (--nLogNumIndex > 0) //��С��ţ��Դ˸�����־����
		{
			strOldName = m_strFilePath + "." + std::to_string(nLogNumIndex);
			if (_access(strOldName.c_str(), 0) != -1) //����ļ����Ƿ���ڣ��������򴴽�
			{
				rename(strOldName.c_str(), strNewName.c_str()); //ɾ��
			}
			strNewName = m_strFilePath + "." + std::to_string(nLogNumIndex);
		}

#elif defined OS_LINUX
		if (access(strNewName.c_str(), 0) == F_OK)                                                 //����ļ����Ƿ���ڣ��������򴴽�
		{
			remove(strNewName.c_str()); //ɾ��
		}
		while (--nLogNumIndex > 0) //��С��ţ��Դ˸�����־����
		{
			strOldName = m_strFilePath + "." + std::to_string(nLogNumIndex);
			if (access(strOldName.c_str(), 0) == F_OK) //����ļ����Ƿ���ڣ��������򴴽�
			{
				rename(strOldName.c_str(), strNewName.c_str()); //ɾ��
			}
			strNewName = m_strFilePath + "." + std::to_string(nLogNumIndex);
		}
#endif
		rename(m_strFilePath.c_str(), strNewName.c_str()); //������
		m_logStream.open(m_strFilePath, std::fstream::app);
	}
	return true;
}

void mmrUtil::CLogger::dealThread()
{
	while (m_bRunning.load(std::memory_order_relaxed))
	{
		if (m_pBufWrite->getSize() > 0 || m_queBufsWrite.size() > 0)
		{
			{
				std::unique_lock<std::mutex> lock(m_mutWrite);
				updateBufWrite();
				m_queBufsDeal = std::move(m_queBufsWrite);
			}

			while (m_queBufsDeal.size())
			{
				m_pBufDeal = std::move(m_queBufsDeal.front());
				m_queBufsDeal.pop();
				std::cout << "log write!" << std::endl;
				m_logStream << m_pBufDeal->getBuf();
				m_logStream.flush();
				m_pBufDeal->clear();

				{
					std::unique_lock<std::mutex> lock(m_mutWrite);
					m_queBufsEmpty.push(std::move(m_pBufDeal));
				}
			}
		}

		{
			std::unique_lock<std::mutex> lock(m_mutWrite);
			m_cv.wait_for(lock, std::chrono::milliseconds(100000));
		}
	}
}

void mmrUtil::CLogger::updateBufWrite()
{
	m_queBufsWrite.push(std::move(m_pBufWrite));
	if (m_queBufsEmpty.size())
	{
		m_pBufWrite = std::move(m_queBufsEmpty.front());
		m_queBufsEmpty.pop();
	}
	else
	{
		//�Ƿ��������������
		m_pBufWrite = std::make_unique<CBigBuff>(m_ulBigBufSize);
	}
}

