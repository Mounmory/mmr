#include "Common_def.h"

#ifdef OS_WIN
//#include <iostream>
//#include <map>
//#include <functional>
//
//// 定义一个通用的函数指针类型
//template<typename ReturnType, typename... Args>
//using FuncPtr = std::function<ReturnType(Args...)>;
//
//// 定义一个通用的函数类型
//template<typename ReturnType, typename... Args>
//using Function = ReturnType(*)(Args...);
//
//// 合并多个map的函数
//template<typename ReturnType, typename... Args>
//std::map<std::string, FuncPtr<ReturnType, Args...>> mergeMaps(std::map<std::string, FuncPtr<ReturnType, Args...>>... maps) {
//	std::map<std::string, FuncPtr<ReturnType, Args...>> mergedMap;
//	(mergedMap.insert(maps.begin(), maps.end()), ...);
//	return mergedMap;
//}
//
//// 具有不同参数和返回值的函数
//int increment(int num) {
//	return num + 1;
//}
//
//float square(float num) {
//	return num * num;
//}
//
//int main() {
//	// 创建两个map
//	std::map<std::string, FuncPtr<int, int>> intFuncMap;
//	std::map<std::string, FuncPtr<float, float>> floatFuncMap;
//
//	// 添加函数指针到map
//	intFuncMap["increment"] = increment;
//	floatFuncMap["square"] = square;
//
//	// 合并两个map为一个通用的map
//	auto mergedMap = mergeMaps(intFuncMap, floatFuncMap);
//
//	// 调用函数指针
//	int result1 = mergedMap["increment"](5);
//	float result2 = mergedMap["square"](2.5f);
//
//	std::cout << "Result 1: " << result1 << std::endl;
//	std::cout << "Result 2: " << result2 << std::endl;
//
//	return 0;
//}

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
	std::cout << "windows test..." << std::endl;
	if (argc >= 2) {
		std::cout << "args[1]: " << std::string(argv[1]) << std::endl;
		std::cout << "args[2]: " << std::string(argv[2]) << std::endl;
	}

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

#elif defined OS_LINUX
#include <iconv.h>
#include <iostream>
#include <string>
#include <string.h>
#include <malloc.h>

int code_convert(const char *from_charset,
	const char *to_charset,
	char *inbuf,
	size_t inlen,
	char *outbuf,
	size_t outlen) {
	iconv_t cd;
	char **pin = &inbuf;
	char **pout = &outbuf;

	cd = iconv_open(to_charset, from_charset);
	if (cd == 0)
	{
		std::cout << "open failed!" << std::endl;
		return -1;
	}


	memset(outbuf, 0, outlen);

	if ((int)iconv(cd, pin, &inlen, pout, &outlen) == -1)
	{
		iconv_close(cd);
		std::cout << "iconv failed!" << std::endl;
		return -1;
	}
	iconv_close(cd);
	*pout = '\0';
	std::cout << "code_convert end!" << std::endl;

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}

int u2g(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("utf-8", "gb2312", inbuf, inlen, outbuf, outlen);
}

int g2u(char *inbuf, size_t inlen, char *outbuf, size_t outlen) {
	return code_convert("gb2312", "utf-8", inbuf, inlen, outbuf, outlen);
}

std::string GBKToUTF8(const std::string& strGBK)
{
	int length = strGBK.size() * 2 + 1;

	char *temp = (char*)malloc(sizeof(char)*length);

	if (g2u((char*)strGBK.c_str(), strGBK.size(), temp, length) >= 0)
	{
		std::string str_result;
		str_result.append(temp);
		free(temp);
		return str_result;
	}
	else
	{
		std::cout << "GBKToUTF8 failed!" << std::endl;
		free(temp);
		return "";
	}
}

std::string UTFtoGBK(const char* utf8)
{
	int length = strlen(utf8);

	char *temp = (char*)malloc(sizeof(char)*length);

	if (u2g((char*)utf8, length, temp, length) >= 0)
	{
		std::string str_result;
		str_result.append(temp);
		free(temp);

		return str_result;
	}
	else
	{
		std::cout << "UTFtoGBK failed!" << std::endl;
		free(temp);
		return "";
	}
}

int main(int argc, char **argv)
{
	std::cout << "linux test..." << std::endl;
	if (argc >= 2) {
		std::cout << "args[1]: " << std::string(argv[1]) << std::endl;
		std::cout << "args[2]: " << std::string(argv[2]) << std::endl;
	}

	std::string teststr = u8"测试字符串";

	std::cout << "原始字符串：" << teststr.c_str() << std::endl;

	std::cout << "UTF8转换GBK后的字符串：" << UTFtoGBK(teststr.c_str()).c_str() << std::endl;

	std::cout << "GBK转换UTF8后的字符串：" << GBKToUTF8(UTFtoGBK(teststr.c_str()).c_str()).c_str() << std::endl;

	getchar();

	return 0;
}
#endif
