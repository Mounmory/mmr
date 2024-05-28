﻿#ifndef CLOGGER_H
#define CLOGGER_H
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

BEGINE_NAMESPACE(mmrUtil)

	enum class emLogLevel
	{
		Log_Off = -1,
		Log_Forece = 0,
		Log_Fatal,
		Log_Error,
		Log_Warn,
		Log_Info,
		Log_Debug
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
		if (ulLen < 2048)
		{
			std::cerr << "[" << __FUNCTION__ << "][" << __LINE__ << "CBigBuff construct init size is less than 2048!" << std::endl;
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

	void LogForce(const char *format, ...);
	void LogFatal(const char *format, ...);
	void LogError(const char *format, ...);
	void LogWarn(const char *format, ...);
	void LogInfo(const char *format, ...);
	void LogDebug(const char *format, ...);

	emLogLevel getLevel() { return m_LogLevel; }

	//使用双缓冲队列写日志接口
	void logWrite(const char *format, ...);
private:
	void dealThread();

	void updateBufWrite();

	void fileSizeCheck();//检查文件大小
private:
	emLogLevel m_LogLevel;

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


struct LogWrapper 
{
	emLogLevel logLevel = emLogLevel::Log_Debug;
	CLogger* loger = CLogger::getLogger();
};



END_NAMESPACE(mmrUtil)


#if MMR_LOGGER_WRAP//使用日志封装，每个模块单独控制日志等级
#define logInstancePtr mmrUtil::CLogger::getLogger()
extern std::shared_ptr<mmrUtil::LogWrapper> g_LoggerPtr;

#define LOG_FORCE(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Forece)\
   g_LoggerPtr->loger->logWrite("[%d][A][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_FATAL(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Fatal)\
   g_LoggerPtr->loger->logWrite("[%d][F][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Error)\
   g_LoggerPtr->loger->logWrite("[%d][E][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR_PRINT(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Error)\
   g_LoggerPtr->loger->logWrite("[%d][A][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)\
	,printf("[%d][A][%s][%d]" format "\n", Thread_ID, __FUNCTION__, __LINE__, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Warn)\
   g_LoggerPtr->loger->logWrite("[%d][W][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Info)\
   g_LoggerPtr->loger->logWrite("[%d][I][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
if(g_LoggerPtr->logLevel >= mmrUtil::emLogLevel::Log_Debug)\
   g_LoggerPtr->loger->logWrite("[%d][D][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#else
#define logInstancePtr mmrUtil::CLogger::getLogger()

#define LOG_FORCE(format, ...) \
   logInstancePtr->LogForce("[%d][A][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_FATAL(format, ...) \
   logInstancePtr->LogFatal("[%d][F][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR(format, ...) \
   logInstancePtr->LogError("[%d][E][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_ERROR_PRINT(format, ...) \
	logInstancePtr->LogError("[%d][E][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__);\
   printf("[%d][A][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_WARN(format, ...) \
   logInstancePtr->LogWarn("[%d][W][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_INFO(format, ...) \
   logInstancePtr->LogInfo("[%d][I][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)

#define LOG_DEBUG(format, ...) \
   logInstancePtr->LogDebug("[%d][D][%s][%d]" format "\n",Thread_ID, __FUNCTION__,__LINE__, ##__VA_ARGS__)
#endif


#endif