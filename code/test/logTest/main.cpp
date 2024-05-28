#include "Common_def.h"
#include "util/Clogger.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>	

class CSizeTest 
{
public:
	int a1;
	//int a2;
	char b;
	//char c;
	//long d;
};




std::atomic_bool g_atoStart;

std::shared_ptr<mmrUtil::LogWrapper> g_LoggerPtr;

void logThread() 
{
	while (!g_atoStart.load());

	std::cout << "write log start!" << std::endl;

	for (int i = 0; i < 10000000; ++i)
	{
		//LOG_FORCE("log test i value log test i value log test i value log test i value is %d!", i);
	}
}

int main()
{
	//std::cout << "类大小" << sizeof(CSizeTest) << std::endl;
	g_LoggerPtr = std::make_shared<mmrUtil::LogWrapper>();
	g_LoggerPtr->loger->start();
	//logInstancePtr->start();

	for (int i = 0; i < 10000000; ++i)
	{
		LOG_FORCE("log test i value log test i value log test i value log test i value is %d!", i);
		//std::cout << "i value is" << i << std::endl;
		//std::this_thread::sleep_for(std::chrono::microseconds(10));
	}
	//g_atoStart.store(false);
	//std::vector<std::thread> vecThread;
	//for (int i = 0 ; i< 8;++i)
	//{
	//	vecThread.emplace_back(std::thread(logThread));
	//}
	//g_atoStart.store(true);
	//for (auto& iterThread : vecThread)
	//{
	//	iterThread.join();
	//}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();

	return 0;
}
