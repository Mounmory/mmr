#include "util/Clogger.h"
#include "util/UtilFunc.h"
#include <stdarg.h>
#include <iostream>
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

#define LOG_BY_LEVEL(logLevel,logTag)\
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
<< "[" << #logTag << "]" << strBufPtr << std::endl


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

	LOG_FORCE("----------------- start -----------------");
	return true;
}

void mmrUtil::CLogger::stop()
{
	if (m_logStream.is_open())
	{
		m_logStream.close();
	}
}

void mmrUtil::CLogger::LogForce(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_FORCE, O);
}

void mmrUtil::CLogger::LogFatal(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_FATAL, F);
}

void mmrUtil::CLogger::LogError(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_ERROR, E);
}

void mmrUtil::CLogger::LogWarn(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_WARN, W);
}

void mmrUtil::CLogger::LogInfo(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_INFO, I);
}

void mmrUtil::CLogger::LogDebug(const char *format, ...)
{
	LOG_BY_LEVEL(emLogLevel::LOG_DEBUG, D);
}

std::fstream & mmrUtil::CLogger::LogByOstream(const char* logTag /*= ""*/)
{
	if (LogCheck(emLogLevel::LOG_FORCE))
	{
		auto now = std::chrono::system_clock::now(); 
		auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000; 
		std::time_t current_time = std::chrono::system_clock::to_time_t(now); 
		std::tm* time_info = std::localtime(&current_time); 
		m_logStream << "[" << std::this_thread::get_id() << "]"
			<< (time_info->tm_year + 1900) << "-" << std::setfill('0') << std::setw(2) << (time_info->tm_mon + 1) << "-" << std::setfill('0') << std::setw(2) << time_info->tm_mday
			<< " " << std::setfill('0') << std::setw(2) << time_info->tm_hour << ":" << std::setfill('0') << std::setw(2) << time_info->tm_min << ":"
			<< std::setfill('0') << std::setw(2) << time_info->tm_sec << "." << std::setfill('0') << std::setw(3) << now_ms
			<< "[" << logTag << "]";

	}
	return m_logStream;
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

