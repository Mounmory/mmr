#include "Common_def.h"

#include <iostream>
#include "Common_def.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"
#include "util/Clogger.h"
#include "CompTest/IHelloService.h"
#include "core/include/CCompFramework.h"

#define MAX_STR_LEN 1024


int main(int argc, char **argv)
{
	//启动日志
	std::string strFilePath;
	CoreFrameworkIns->start(strFilePath);

	auto helloSer = CoreFrameworkIns->getService<IHelloService>();

	if (helloSer)
	{
		helloSer->sayHello();
	}
	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

