#include "Common_def.h"
#include "util/Clogger.h"
#include <iostream>
#include <sstream>

class CSizeTest 
{
public:
	int a1;
	//int a2;
	char b;
	//char c;
	//long d;
};

int main()
{
	std::cout << "类大小" << sizeof(CSizeTest) << std::endl;

	logInstancePtr->start();

	for (int i = 0 ; i < 100 ; ++i)
	{
		LOG_FORCE("log test i value is %d!", i);
		//LOG_FORCE("log test                                     i value is %lld!", i);
		//LOG_DEBUG("log test i value is %lld!", i);
		//LOGWARN_BYSTREAM("log test i value is " << i);
		std::cout << "log test i value is " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}


	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
