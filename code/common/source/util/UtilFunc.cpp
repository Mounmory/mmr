#include <sstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include "util/UtilFunc.h"

#ifdef OS_WIN//windows
#include <Windows.h>
#include <codecvt>
#elif defined OS_LINUX//linux
#include <sys/stat.h>
#include <unistd.h>
#include <iconv.h>
#endif

bool mmrUtil::utf8ToLocalString(const std::string& strIn, std::string& strOut)
{
#ifdef OS_WIN
	try
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> localConverter(new std::codecvt_byname<wchar_t, char, std::mbstate_t >(""));
		std::wstring wstr = converter.from_bytes(strIn);
		strOut = localConverter.to_bytes(wstr);
		return true;
	}
	catch (...)
	{
		strOut.clear();
		return false;
	}
#elif defined OS_LINUX
	//linux下转换
	//https://www.cnblogs.com/huojing/articles/16291647.html

	iconv_t iconvDescriptor = iconv_open("gb2312", "UTF-8");
	if (iconvDescriptor == (iconv_t)-1) 
	{
		std::cerr << "iconv_open failed!" << std::endl;
		return false;
	}

	const char* inputBuffer = strIn.c_str();
	size_t inputSize = strIn.size();
	size_t outputSize = inputSize * 2; // 估计输出缓冲区的大小

	strOut.resize(outputSize);
	char* outputPointer = const_cast<char*>(strOut.c_str());

	if (iconv(iconvDescriptor, (char**)&inputBuffer, &inputSize, &outputPointer, &outputSize) == (size_t)-1) 
	{
		std::cerr << "convert utf8 to local failed" << std::endl;
		iconv_close(iconvDescriptor);
		return false;
	}
	iconv_close(iconvDescriptor);
	return true;
#endif //OS_WIN
}

bool mmrUtil::localStringToUtf8(const std::string& strIn, std::string& strOut)
{
#ifdef OS_WIN
	try
	{
		std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> localConverter(new std::codecvt_byname<wchar_t, char, std::mbstate_t >(""));
		std::wstring wstr = localConverter.from_bytes(strIn);
		strOut = converter.to_bytes(wstr);
		return true;
	}
	catch (...)
	{
		strOut.clear();
		return false;
	}
#elif defined OS_LINUX
	iconv_t iconvDescriptor = iconv_open("UTF-8", "gb2312");
	if (iconvDescriptor == (iconv_t)-1) 
	{
		std::cerr << "iconv_open failed!" << std::endl;
		return false;
	}

	const char* inputBuffer = strIn.c_str();
	size_t inputSize = strIn.size();
	size_t outputSize = inputSize * 4; // 估计输出缓冲区的大小

	strOut.resize(outputSize);
	char* outputPointer = const_cast<char*>(strOut.c_str());

	if (iconv(iconvDescriptor, (char**)&inputBuffer, &inputSize, &outputPointer, &outputSize) == (size_t)-1) 
	{
		std::cerr << "convert local to utf8 failed" << std::endl;
		iconv_close(iconvDescriptor);
		return false;
	}
	iconv_close(iconvDescriptor);
	return true;
#endif //OS_WIN
}


#define MAX_STR_LEN 1024

static uint8_t GetTransFlag() //生成随机8位二进制字节
{
	return (rand() % 256 & 0xFF);//生成一个随机数，取最后一个字节
}


inline void mmrUtil::byteTranslate(const uint8_t* inBuf, const uint16_t nLen, const uint8_t transFlag, uint8_t* outBuf)
{
	//解密为原字符
	for (int i = 0; i < nLen; ++i)
	{
		outBuf[i] = inBuf[i] ^ (transFlag >> (i % 8));
	}
}

bool mmrUtil::stringToCode(const std::string strIn, std::string& strOut)
{
	if (strIn.empty())
	{
		return false;
	}

	std::stringstream ss;
	uint16_t nStrLen = strIn.length();//返回长度

	std::vector<uint8_t> bufTrans(nStrLen + 1, 0);
	bufTrans[nStrLen] = GetTransFlag();//用于异或运算的一个字节
	byteTranslate((const uint8_t*)strIn.c_str(), nStrLen, bufTrans[nStrLen], &bufTrans[0]);

	for (int i = 0; i <= nStrLen; ++i)
	{
		ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)bufTrans[i];
	}
	strOut = ss.str();

	return true;
}

bool mmrUtil::codeToString(const std::string strIn, std::string& strOut)
{
	if (strIn.empty() || (strIn.length() % 2))//为空或者为奇数
	{
		return false;
	}

	uint16_t nStrLen = strIn.length() / 2;//返回长度
	std::vector<uint8_t> bufTrans(nStrLen, 0);

	//将字符串转换为字节
	uint8_t h1, h2;
	uint8_t s1, s2;
	for (int i = 0; i < nStrLen; i++)
	{
		h1 = strIn[2 * i];
		h2 = strIn[2 * i + 1];
		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;
		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;
		bufTrans[i] = s1 * 16 + s2;
	}

	strOut.resize(nStrLen - 1);
	char* pDesStr = const_cast<char*>(strOut.c_str());
	byteTranslate(&bufTrans[0], nStrLen - 1, bufTrans[nStrLen - 1], (uint8_t*)pDesStr);

	return true;
}

COMMON_FUN_API bool mmrUtil::getAppPathAndName(std::string& filePath, std::string& exeName)
{
#ifdef OS_WIN
	char path[MAX_STR_LEN];
	auto pathLen = GetModuleFileName(NULL, path, MAX_STR_LEN);
	if (pathLen > MAX_STR_LEN)
	{
		std::cerr << "funciton mmrUtil::getAppPathAndName path len[" << pathLen << "] is longer than max string leng " << std::endl;
	}
	filePath = path;

	auto pos = filePath.rfind('.');
	if (pos != std::string::npos) 
	{
		filePath.erase(filePath.begin() + pos, filePath.end());
	}
	pos = filePath.rfind('\\');
	if (pos != std::string::npos)
	{
		exeName = &filePath.c_str()[pos + 1];
		filePath.erase(filePath.begin() + pos + 1, filePath.end());
	}
	else
	{
		return false;
	}
	return true;
#else
	char tmpPath[MAX_STR_LEN];//路径
	char tmpName[MAX_STR_LEN];//exe名称
	char *path_end;
	if (readlink("/proc/self/exe", tmpPath, MAX_STR_LEN) <= 0)
		return false;
	path_end = strrchr(tmpPath, '/');
	if (path_end == NULL)
		return false;
	++path_end;
	strcpy(tmpName, path_end);
	*path_end = '\0';
	filePath = tmpPath;
	exeName = tmpName;
	return true;
#endif
}

COMMON_FUN_API std::string mmrUtil::generateGUID()
{
	std::string retStr;
#ifdef OS_WIN
	//GUID guid;
	//if (CoCreateGuid(&guid) == RPC_S_OK) {
	//	// 将GUID转换为字符串形式
	//	char guidStr[39];
	//	StringFromGUID2(guid, guidStr, sizeof(guidStr) / sizeof(guidStr[0]));

	//	// 输出GUID
	//	std::cout << "Generated GUID: " << guidStr << std::endl;
	//}

#else



#endif

	return retStr;
}

COMMON_FUN_API std::string mmrUtil::getComplieTime()
{
	return std::string(__DATE__) + " " + std::string(__TIME__);
}

COMMON_FUN_API const char* mmrUtil::getFileName(const char* szFullPath)
{
	char* p = (char*)szFullPath;
	while (*p) ++p;
	while (--p >= szFullPath) {
#ifdef OS_WIN
		if (*p == '/' || *p == '\\')
#else
		if (*p == '/')
#endif
			return ++p;
	}
	return szFullPath;
}

