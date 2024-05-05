#include "Common_def.h"
#include "util/CVarDatas.hpp"
#include <iostream>


int main()
{
	try
	{
		mmrUtil::CVarDatas vData;
		vData["int"] = 10;
		vData["string"] = "hello!";
		std::cout << "int data is " << vData["int"].getInt32Data()<< std::endl;
		std::cout << "string data is " << vData["string"].getStringData() << std::endl;
		std::cout << "other data is " << vData["other"].getStringData() << std::endl;
	}
	catch (std::exception& e)
	{
		std::cout << "exception info is " << e.what();
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;

}
