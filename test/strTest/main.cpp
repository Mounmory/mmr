#include <iostream>
#include "Common.h"
#include "util/UtilFunc.h"

#define MAX_STR_LEN 1024

void UTF8LocalTest();

void byteCodeConvertTest();

int main() 
{
	UTF8LocalTest();

	byteCodeConvertTest();

	system("pause");
	return 0;
}


void UTF8LocalTest()
{
	//std::string strlocal = "你好";
	char strlocal[512] = "你好";
	std::cout << "1 local ：" << strlocal << std::endl;
	std::string strUTF;
	MmrCommon::localStringToUtf8(strlocal, strUTF);
	std::cout << "2 utf8 ：" << strUTF << std::endl;
	std::string strLocal;
	MmrCommon::utf8ToLocalString(strUTF, strLocal);
	std::cout << "3 local ：" << strLocal << std::endl;
}

void byteCodeConvertTest()
{
	char szInput[MAX_STR_LEN] = { 0 };
	char szOutput[2 * MAX_STR_LEN] = { 0 };
	char szInputConvert[MAX_STR_LEN] = { 0 };

	while (true)
	{
		memset(szInput, 0, sizeof(szInput));
		memset(szOutput, 0, sizeof(szOutput));
		printf("---------------- begin ------------------\n");
		printf("输入要加密的字符：\n");
		scanf("%s", szInput);
		MmrCommon::byteToCode((uint8_t*)szInput, (uint8_t*)szOutput);
		printf("加密以后为：\n%s\n", szOutput);

		printf("输入解密的字符：\n");
		scanf("%s", szInput);
		MmrCommon::codeToByte((uint8_t*)szInput, (uint8_t*)szOutput);
		printf("解密以后为：\n%s\n", szOutput);
		printf("---------------- end ------------------\n\n");
	}
}

