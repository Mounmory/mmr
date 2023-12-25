#include "util/UtilFunc.h"

using namespace MmrCommon;

bool MmrCommon::utf8ToLocalString(const std::string& strIn, std::string& strOut)
{
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
}

bool MmrCommon::localStringToUtf8(const std::string& strIn, std::string& strOut)
{
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
}

#define MAX_STR_LEN 1024

static uint8_t GetTransFlag() //生成随机8位二进制字节
{
	return (rand() % 256 & 0xFF);//生成一个随机数，取最后一个字节
}

uint16_t MmrCommon::byteToCode(const uint8_t* byteIn, uint8_t* codeOut, uint16_t nlenInput/* = 0*/)
{
	uint16_t nLen = nlenInput > 0 ? nlenInput : strlen((char*)byteIn);
	if (nLen <= 0)
	{
		return 0;
	}

	static uint8_t* byTempSrc = new uint8_t[MAX_STR_LEN];
	uint8_t* temPtr = nullptr;

	uint16_t nRet = 2 * nLen + 2;//返回长度
	if (nRet > MAX_STR_LEN)
	{
		temPtr = byTempSrc;
		byTempSrc = new uint8_t[nRet + 1];
	}

	unsigned char TransFlag = GetTransFlag();//用于异或运算的一字节
	memcpy(byTempSrc, byteIn, nLen);
	byTempSrc[nLen] = TransFlag;//将运算字节附到信息尾部
								//进行异或加密
	for (int i = 0; i < nLen; ++i)
	{
		byTempSrc[i] ^= TransFlag >> (i % 8);
	}
	//将二进制转换为字符串输出
	char sztmp[4];
	//memset(codeOut, 0, nRet + 1);
	for (int i = 0; i <= nLen; ++i)
	{
		sprintf_s(sztmp, "%02X", byTempSrc[i]);
		memcpy(&codeOut[2 * i], sztmp, 2);
	}
	codeOut[nRet] = 0x00;
	if (temPtr != nullptr)
	{
		delete byTempSrc;
		byTempSrc = temPtr;
		temPtr = nullptr;
	}
	return nRet;
}

uint16_t MmrCommon::codeToByte(const uint8_t* ocdeIn, uint8_t* byteOut)
{
	uint16_t nLenSrc = strlen((char*)ocdeIn);
	uint16_t nLenDes = nLenSrc / 2;
	if (nLenDes <= 0)
	{
		return 0;
	}
	//将字符串转换为字节
	uint8_t h1, h2;
	uint8_t s1, s2;
	for (int i = 0; i < nLenDes; i++)
	{
		h1 = ocdeIn[2 * i];
		h2 = ocdeIn[2 * i + 1];
		s1 = toupper(h1) - 0x30;
		if (s1 > 9)
			s1 -= 7;
		s2 = toupper(h2) - 0x30;
		if (s2 > 9)
			s2 -= 7;
		byteOut[i] = s1 * 16 + s2;
	}
	//解密为原字符
	for (int i = 0; i < nLenDes - 1; ++i)
	{
		byteOut[i] ^= byteOut[nLenDes - 1] >> (i % 8);
	}
	byteOut[nLenDes - 1] = 0x00;
	return nLenDes - 1;
}
