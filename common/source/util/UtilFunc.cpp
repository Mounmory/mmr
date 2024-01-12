#include <sstream>
#include <iomanip>
#include <iostream>
#include "util/UtilFunc.h"

#ifdef OS_WIN//windows
#include <Windows.h>
#include <codecvt>
#elif defined OS_LINUX//linux
#include <sys/stat.h>
#include <unistd.h>
#include <iconv.h>
#endif

bool MmrCommon::utf8ToLocalString(const std::string& strIn, std::string& strOut)
{
#ifdef OS_WIN
	try
	{
		static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		static std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> localConverter(new std::codecvt_byname<wchar_t, char, std::mbstate_t >(""));
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

bool MmrCommon::localStringToUtf8(const std::string& strIn, std::string& strOut)
{
#ifdef OS_WIN
	try
	{
		static std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
		static std::wstring_convert<std::codecvt_byname<wchar_t, char, std::mbstate_t>> localConverter(new std::codecvt_byname<wchar_t, char, std::mbstate_t >(""));
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


inline void MmrCommon::byteTranslate(const uint8_t* inBuf, const uint16_t nLen, const uint8_t transFlag, uint8_t* outBuf)
{
	//解密为原字符
	for (int i = 0; i < nLen; ++i)
	{
		outBuf[i] = inBuf[i] ^ (transFlag >> (i % 8));
	}
}

bool MmrCommon::stringToCode(const std::string strIn, std::string& strOut)
{
	static uint8_t* pByteTrans = new uint8_t[MAX_STR_LEN];

	if (strIn.empty())
	{
		return false;
	}

	uint8_t* temBytePtr = nullptr;
	uint16_t nStrLen = strIn.length();//返回长度
	if (nStrLen >= MAX_STR_LEN)
	{
		temBytePtr = pByteTrans;
		pByteTrans = new uint8_t[nStrLen + 1];
	}

	pByteTrans[nStrLen] = GetTransFlag();//用于异或运算的一个字节
	byteTranslate((const uint8_t*)strIn.c_str(), nStrLen, pByteTrans[nStrLen], pByteTrans);

	std::stringstream ss;
	for (int i = 0; i <= nStrLen; ++i)
	{
		ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)pByteTrans[i];
	}
	strOut = ss.str();

	if (temBytePtr != nullptr)
	{
		delete pByteTrans;
		pByteTrans = temBytePtr;
		temBytePtr = nullptr;
	}
	return true;
}

bool MmrCommon::codeToString(const std::string strIn, std::string& strOut)
{
	static uint8_t* pByteTrans = new uint8_t[MAX_STR_LEN];

	if (strIn.empty())
	{
		return false;
	}

	uint8_t* temBytePtr = nullptr;
	uint16_t nStrLen = strIn.length() / 2;//返回长度
	if (nStrLen > MAX_STR_LEN)
	{
		temBytePtr = pByteTrans;
		pByteTrans = new uint8_t[nStrLen];
	}

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
		pByteTrans[i] = s1 * 16 + s2;
	}

	strOut.resize(nStrLen - 1);
	char* pDesStr = const_cast<char*>(strOut.c_str());
	byteTranslate(pByteTrans, nStrLen - 1, pByteTrans[nStrLen - 1], (uint8_t*)pDesStr);

	if (temBytePtr != nullptr)
	{
		delete pByteTrans;
		pByteTrans = temBytePtr;
		temBytePtr = nullptr;
	}
	return true;
}

COMMON_FUN_API bool MmrCommon::GetAppPathAndName(std::string& filePath, std::string& exeName)
{
#ifdef OS_WIN
	char path[MAX_STR_LEN];
	GetModuleFileName(NULL, path, MAX_STR_LEN);
	filePath = path;

	int pos = filePath.rfind('\\');
	if (pos != std::string::npos)
	{
		exeName = &filePath.c_str()[pos + 1];
		filePath.erase(filePath.begin() + pos, filePath.end());
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

