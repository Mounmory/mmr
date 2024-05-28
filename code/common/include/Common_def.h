#ifndef COMMON_H
#define COMMON_H

#if defined(_WIN64) || defined(WIN32)
#define OS_WIN
#elif defined(linux) || defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
#define OS_LINUX
//#elif defined(unix) || defined(__unix) || defined(__unix__)
//#define MMR_UNIX
#endif

#define BEGINE_NAMESPACE(ns) namespace ns {
#define END_NAMESPACE(ns) }

#define IN
#define OUT

#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

#ifdef OS_WIN
#include <windows.h>  

#define DIR_SEPARATOR       '\\'
#define DIR_SEPARATOR_STR   "\\"

#define Thread_ID GetCurrentThreadId()
#else
#include <pthread.h>  
#include <unistd.h>  
#include <sys/syscall.h>  
#include <string>

#define DIR_SEPARATOR       '/'
#define DIR_SEPARATOR_STR   "/"

#define Thread_ID syscall(SYS_gettid)

static std::string _CutParenthesesNTail(std::string&& prettyFuncon)
{
	auto pos = prettyFuncon.find('(');
	if (pos != std::string::npos)
		prettyFuncon.erase(prettyFuncon.begin() + pos, prettyFuncon.end());
	pos = prettyFuncon.find(' ');
	if (pos != std::string::npos)//删除返回类型
		prettyFuncon.erase(prettyFuncon.begin(), prettyFuncon.begin() + pos + 1);
	return std::move(prettyFuncon);
}
#define __FUNCTION__ _CutParenthesesNTail(__PRETTY_FUNCTION__).c_str()//系统自带的宏不显示作用域信息
#endif

#ifndef __FILENAME__
// #define __FILENAME__  (strrchr(__FILE__, DIR_SEPARATOR) ? strrchr(__FILE__, DIR_SEPARATOR) + 1 : __FILE__)
#define __FILENAME__  (strrchr(DIR_SEPARATOR_STR __FILE__, DIR_SEPARATOR) + 1)
#endif


#endif

