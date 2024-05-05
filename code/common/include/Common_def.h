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

#ifdef OS_LINUX//定义函数宏
#include <string>
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
#define __FUNCTION__ _CutParenthesesNTail(__PRETTY_FUNCTION__).c_str()
#endif

#include <chrono>
#include <ctime>
#include <thread>
#include <iomanip>

#define PRINT_LOG(log) \
	{\
	auto now = std::chrono::system_clock::now(); \
	auto now_ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count() % 1000;\
	std::time_t current_time = std::chrono::system_clock::to_time_t(now);\
	std::tm* time_info = std::localtime(&current_time);\
	std::cout << "[" << std::this_thread::get_id() << "]"\
	<< (time_info->tm_year + 1900) << "-" << std::setfill('0') << std::setw(2) << (time_info->tm_mon + 1) << "-" << std::setfill('0') << std::setw(2)<< time_info->tm_mday\
	<< " " << std::setfill('0') << std::setw(2) << time_info->tm_hour << ":" << std::setfill('0') << std::setw(2) << time_info->tm_min << ":"\
	<< std::setfill('0') << std::setw(2) << time_info->tm_sec << "." << std::setfill('0') << std::setw(3) << now_ms\
	<< log << std::endl;\
	}

#endif