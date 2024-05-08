#ifndef CLOGGER_H
#define CLOGGET_H
#include "Common_def.h"
#include "util/UtilExport.h"
#include <mutex>
#include <fstream>


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

	void LogForce(const char *format, ...);
	void LogFatal(const char *format, ...);
	void LogError(const char *format, ...);
	void LogWarn(const char *format, ...);
	void LogInfo(const char *format, ...);
	void LogDebug(const char *format, ...);

	std::fstream &LogByOstream(const char* logTag = "");
	std::mutex& getMutex() { return m_mutWrite; }
	emLogLevel getLevel() { return m_LogLevel; }
private:
	bool LogCheck(emLogLevel level);

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

	std::fstream m_logStream;   //写文件流
	std::mutex	m_mutWrite;  //进行客户端句柄存储修改时，线程锁

};

END_NAMESPACE(mmrUtil)

#define logInstancePtr mmrUtil::CLogger::getLogger()

#define LOG_FORCE(format, ...) \
   logInstancePtr->LogForce("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_FATAL(format, ...) \
   logInstancePtr->LogFatal("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
   logInstancePtr->LogError("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
   logInstancePtr->LogWarn("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
   logInstancePtr->LogInfo("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
   logInstancePtr->LogDebug("[%s][%d]" format, __FUNCTION__,__LINE__, ##__VA_ARGS__)

//直接使用文件流输出
#define LOGFORCE_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_FORCE)\
		logInstancePtr->LogByOstream("O") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}

#define LOGFATAL_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_FATAL)\
		logInstancePtr->LogByOstream("F") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}

#define LOGERROR_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_ERROR)\
	logInstancePtr->LogByOstream("E") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}

#define LOGWARN_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_WARN)\
	logInstancePtr->LogByOstream("W") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}

#define LOGINFO_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_INFO)\
	logInstancePtr->LogByOstream("I") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}

#define LOGDEBUG_BYSTREAM(logInfo)\
{\
	std::lock_guard<std::mutex> lockLog(logInstancePtr->getMutex());\
	if (logInstancePtr->getLevel() >= mmrUtil::emLogLevel::LOG_DEBUG)\
		logInstancePtr->LogByOstream("D") << "[" << __FUNCTION__ << "][" <<__LINE__ << "]" << logInfo <<std::endl;\
}
#endif