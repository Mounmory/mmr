#ifndef CLOGGER_H
#define CLOGGET_H
#include "Common_def.h"
#include "util/UtilExport.h"
#include <mutex>
#include <condition_variable>
#include <atomic>
#include <memory>
#include <fstream>
#include <string.h>
#include <iostream>
#include <queue>

#if defined(OS_WIN)  
#include <windows.h>  
#define Thread_ID GetCurrentThreadId()

#elif defined(OS_LINUX)  
#include <pthread.h>  
#include <unistd.h>  
#include <sys/syscall.h>  
#define THREAD_ID syscall(SYS_gettid)

#else
error os
#endif  

BEGINE_NAMESPACE(mmrUtil)

enum class emLogLevel
{
	LOG_OFF = -1,
	LOG_FORCE = 0,
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG
};


class CBigBuff 
{
public:
	CBigBuff() = delete;
	CBigBuff(CBigBuff&) = delete;
	CBigBuff(CBigBuff&&) = delete;

	CBigBuff(uint32_t ulLen)
		: m_buf(new char[ulLen])
		, m_ulLen(ulLen - 1)//长度-1，避免添最后一位置空越界
		, m_ulPos(0)
		, m_usTryIncrease(0)
	{
		if (!ulLen)
		{
			std::cerr << "CBigBuff construct init size is zero!" << std::endl;
		}
	};

	~CBigBuff() 
	{
		delete[] m_buf;
	}

	void tryWrite(char* buf, uint16_t len) 
	{
		memcpy(m_buf + m_ulPos, buf, len);
		m_usTryIncrease += len;
	}

	void doneTry() {
		m_ulPos += m_usTryIncrease;
		m_usTryIncrease = 0;
	}

	void clearTry() 
	{ 
		m_usTryIncrease = 0;
		m_buf[m_ulPos] = 0x00;
	}

	uint32_t getTryAvailid() { return (m_ulLen - m_ulPos - m_usTryIncrease); }

	char* getTryCurrent() { return (m_buf + m_ulPos + m_usTryIncrease); }

	void addTryIncrease(uint16_t weakLen) { m_usTryIncrease += weakLen; }

	void clear() {
		m_ulPos = 0; 
		m_usTryIncrease = 0;
	}

	char* getBuf() { return m_buf; }

	uint32_t getMaxLen() { return m_ulLen; }

	uint32_t getSize() { return m_ulPos; }


private:
	char* m_buf;
	uint32_t m_ulLen;//buf长度
	uint32_t m_ulPos;//当前buf位置
	uint32_t m_usTryIncrease;
};

class COMMON_CLASS_API CLogger
{
private:
	CLogger();
	~CLogger();
public:
	static CLogger* getLogger();

	bool setFileMaxNum(uint32_t fileNum);
	bool setFileMaxSize(uint64_t fileSize);
	bool setLogLevel(emLogLevel logLevel);

	uint32_t getFileMaxNum() { return m_fileNum; }
	uint64_t getFileMaxSize() { return m_fileSize; }
	emLogLevel getLogLevel() { return m_LogLevel; }

	bool init(const std::string& strPath, const std::string& strName);
	bool start();
	void stop();

	void logWrite(const char *format, ...);

	void LogForce(const char *format, ...);
	void LogFatal(const char *format, ...);
	void LogError(const char *format, ...);
	void LogWarn(const char *format, ...);
	void LogInfo(const char *format, ...);
	void LogDebug(const char *format, ...);

	//std::fstream &LogByOstream(const char* logTag = "");
	//std::mutex& getMutex() { return m_mutWrite; }
	emLogLevel getLevel() { return m_LogLevel; }
private:
	bool LogCheck(emLogLevel level);

	void dealThread();

	void updateBufWrite();

	void fileSizeCheck();//检查文件大小
private:
	emLogLevel m_LogLevel;
	const uint16_t m_lBufLen;
	const uint16_t m_lBigBufLen;
	char* m_pBuf;
	char* m_pBigBuf;

	uint32_t m_fileNum;
	uint64_t m_fileSize;

	std::string m_strLogDir; //当前路径
	std::string m_strLogName; //文件路径
	std::string m_strFilePath; //输出文件全路径

	std::fstream m_logStream;   //写文件流,后续考虑使用更高效的文件流

	
	std::unique_ptr<CBigBuff> m_pBufWrite;//写
	std::unique_ptr<CBigBuff> m_pBufDeal;//写
	std::queue<std::unique_ptr<CBigBuff>> m_queBufsWrite;
	std::queue<std::unique_ptr<CBigBuff>> m_queBufsDeal;
	std::queue<std::unique_ptr<CBigBuff>> m_queBufsEmpty;
	uint16_t m_usBufEmptySize = 3;
	uint32_t m_ulBigBufSize = 1024 * 1024;

	std::mutex	m_mutWrite;  //进行客户端句柄存储修改时，线程锁
	std::condition_variable m_cv;
	std::unique_ptr<std::thread> m_threadDeal;
	std::atomic_bool m_bRunning;


	std::tm m_lastTime;//上一次日志时间
	char m_szLastTime[32];//上一次时间字符串

};

END_NAMESPACE(mmrUtil)

#define logInstancePtr mmrUtil::CLogger::getLogger()

#define LOG_FORCE(format, ...) \
   logInstancePtr->logWrite("[%d][O][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_FATAL(format, ...) \
   logInstancePtr->LogFatal("[F][%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
   logInstancePtr->LogError("[E][%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
   logInstancePtr->LogWarn("[W][%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
   logInstancePtr->LogInfo("[I][%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
   logInstancePtr->LogDebug("[D][%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#endif