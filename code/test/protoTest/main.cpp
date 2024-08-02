#include <iostream>
#include "MyTest.h"
int main(int argc, char* argv[])
{
    MyTest t;
    t.test();

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();

    return 0;
}