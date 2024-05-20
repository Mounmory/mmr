#include "Common_def.h"

#include <iostream>
#include "Common_def.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"

#include "ComponentDemo/IHelloService.h"
#include "core/include/CCompFramework.h"

#define MAX_STR_LEN 1024



int main(int argc, char **argv)
{
	CoreFrameworkIns->start();

	auto helloSer = CoreFrameworkIns->getService<IHelloService>();

	if (helloSer)
	{
		helloSer->sayHello();
	}
	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

