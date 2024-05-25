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

	for (int i = 0 ; i < 10000000 ; ++i)
	{
		LOG_FORCE("log test i value log test i value log test i value log test i value is %d!", i);
	}


	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
