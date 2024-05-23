#include "Common_def.h"

#include <iostream>
#include "Common_def.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"
#include "util/Clogger.h"
#include "ComponentDemo/IHelloService.h"
#include "AppController/ICmdService.h"
#include "core/include/CCompFramework.h"
#include "CAppControler.h"


#define MAX_STR_LEN 1024

int main(int argc, char **argv)
{

	//启动框架
	std::cout << "********************************************" << std::endl << std::endl;
	std::cout << "\t" << mmrUtil::getFileName(argv[0]) << " start...." << std::endl;
	std::cout << "\t" << "complied time: " << mmrUtil::getComplieTime() << std::endl;
	std::cout << "********************************************" << std::endl << std::endl;


	if (CoreFrameworkIns->start())
	{
		auto cmdSer = CoreFrameworkIns->getService<ICmdService>();
		if (cmdSer)
		{
			cmdSer->cmdLoop();
		}
		
	}
	else
	{

	}


	CAppControler appCtl;


	appCtl.run();
	

	//{
	//	auto helloSer = CoreFrameworkIns->getService<IHelloService>();

	//	mmrUtil::CVarDatas varData;
	//	varData.setName("info1");
	//	varData.addVar("name", "test!");
	//	varData.addVar("value", 10);
	//	CoreFrameworkIns->addEvenVartData(std::move(varData));
	//	varData.setName("info2");
	//	CoreFrameworkIns->addEvenVartData(std::move(varData));
	//	if (helloSer)
	//	{
	//		helloSer->sayHello();
	//	}
	//	std::this_thread::sleep_for(std::chrono::seconds(2));
	//}


	//CoreFrameworkIns->stop();

	//for (int i = 0; i < 10000; ++i)
	//{
	//	CoreFrameworkIns->start();

	//	CoreFrameworkIns->stop();
	//	std::cout << "i value is " << i << std::endl;
	//}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

