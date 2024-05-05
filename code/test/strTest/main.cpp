#include "Common_def.h"

#include <iostream>
#include "Common_def.h"
#include "util/UtilFunc.h"
#include "util/CLicenseObj.h"
#include "malloc.h"

#define MAX_STR_LEN 1024

void UTF8LocalTest();

void licTest();

void byteCodeConvertTest();

int main(int argc, char **argv)
{

	//char* pChar = new char[20];
	//std::cout << "size of char " << _msize(pChar) << std::endl;
	//std::cout << "size of char " << malloc_usable_size(pChar) << std::endl;//linux
	
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
	mmrUtil::utf8ToLocalString(strUTF8, strLocal);
	std::cout << "2 local ：" << strLocal << std::endl;
	std::string strUTF_2;
	mmrUtil::localStringToUtf8(strLocal, strUTF_2);
	std::cout << "3 utf8 ：" << strUTF_2 << std::endl;


}

void licTest()
{
	mmrUtil::CLicenseObj pLicObj;
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
			mmrUtil::stringToCode(strIn, strOut);
			std::cout << "加密以后为：" << std::endl;
			std::cout << strOut << std::endl;
		}

		{
			std::string strIn, strOut;
			std::cout << "输入解密的字符：" << std::endl;
			std::getline(std::cin, strIn);
			mmrUtil::codeToString(strIn, strOut);
			std::cout << "解密以后为：" << std::endl; 
			std::cout << strOut << std::endl;
		}
		std::cout << "---------------- end ------------------\n\n" << std::endl;
	}
}

