#include "Common.h"

#include <iostream>
#include "Common.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"

#define MAX_STR_LEN 1024

void UTF8LocalTest();

void licTest();

void byteCodeConvertTest();

int main(int argc, char **argv)
{
	UTF8LocalTest();

	licTest();

	byteCodeConvertTest();

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

void UTF8LocalTest()
{
	std::string strUTF8 = u8"你好";
	//char strlocal[512] = "你好";
	std::cout << "1 UTF8 ：" << strUTF8 << std::endl;
	std::string strLocal;
	MmrCommon::utf8ToLocalString(strUTF8, strLocal);
	std::cout << "2 local ：" << strLocal << std::endl;
	std::string strUTF_2;
	MmrCommon::localStringToUtf8(strLocal, strUTF_2);
	std::cout << "3 utf8 ：" << strUTF_2 << std::endl;


}

void licTest()
{
	MmrCommon::CLicenseObj pLicObj;
	pLicObj.getLicenseState();
}



void byteCodeConvertTest()
{
	std::string strIn, strOut;
	while (true)
	{
		std::cout << "---------------- begin ------------------" << std::endl;
		{
			std::string strIn, strOut;
			std::cout << "输入要加密的字符：" << std::endl;
			std::getline(std::cin, strIn);
			MmrCommon::stringToCode(strIn, strOut);
			std::cout << "加密以后为：" << std::endl;
			std::cout << strOut << std::endl;
		}

		{
			std::string strIn, strOut;
			std::cout << "输入解密的字符：" << std::endl;
			std::getline(std::cin, strIn);
			MmrCommon::codeToString(strIn, strOut);
			std::cout << "解密以后为：" << std::endl; 
			std::cout << strOut << std::endl;
		}
		std::cout << "---------------- end ------------------\n\n" << std::endl;
	}
}

