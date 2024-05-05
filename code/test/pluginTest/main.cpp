#include "Common.h"

#include <iostream>
#include "Common.h"
#include "interface/IToolBase.hpp"
#include "interface/IToolTest.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"
#include "toolCore/CPluginManager.h"

#define MAX_STR_LEN 1024


int main(int argc, char **argv)
{
	auto  plgmng = pluginManager;
	std::string strAppPath, strAppName;
	mmrUtil::GetAppPathAndName(strAppPath, strAppName);
	//plgmng->loadPuglins(strAppPath);
	strAppPath += "/plugins";
	plgmng->loadPuglins(strAppPath);
	auto pluginPtr = plgmng->getTool<MmrTools::IToolTest>();
	if (!pluginPtr)
	{
		std::cout << "nullptr" << std::endl;
	}
	else
	{
		pluginPtr->testHello();
	}
	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

