#include "Common_def.h"
#include "util/Clogger.h"
#include <iostream>

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

	//logInstancePtr->start();

	for (int i = 0 ; i < 100 ; ++i)
	{
		logInstancePtr->LogForce("[%s][%d] log test i value is %lld!", __FUNCTION__, __LINE__, i);
		LOG_INFO("[%s][%d] log test i value is %lld!", __FUNCTION__, __LINE__, i);
		LOGWARN_BYSTREAM("log test i value is " << i);
		std::cout << "log test i value is " << i << std::endl;
	}


	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
