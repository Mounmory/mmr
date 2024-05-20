#include "Common_def.h"

#include <iostream>
#include "Common_def.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"
#include "util/CThreadpool.h"
#include "thread"
#include "chrono"


int addNum(std::string tag, int num1,uint8_t num2);



int main(int argc, char **argv)
{
	threadPooLIntance->start();
	auto ret1 = threadPooLIntance->submit(addNum, "[a]", 100, 20);
	auto ret2 = threadPooLIntance->submit(addNum, "[b]", 500, 20);

	std::cout << "thread 1 return value is " << ret1.get() << std::endl;
	std::cout << "thread 2 return value is " << ret2.get() << std::endl;

	threadPooLIntance->stop();

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

int addNum(std::string tag, int num1, uint8_t num2)
{
	std::cout << tag << "begin!" << std::endl;
	for (uint8_t i = 0 ; i < num2 ; ++i)
	{
		num1 += i;
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
		std::cout << tag << "num1 value now is " << num1 << std::endl;
	}
	std::cout << tag << "end!" << std::endl;
	return num1;
}