#ifndef UTILFUNC_H
#define UTILFUNC_H
#include "Common.h"
#include <string>
#include <codecvt>

namespace MmrCommon 
{
	extern "C" 
	{
		//UTF-8转本地字符
		COMMON_API bool utf8ToLocalString(const std::string& strIn,std::string& strOut);

		//本地字符转UTF-8
		COMMON_API bool localStringToUtf8(const std::string& strIn, std::string& strOut);

		//将字节序转换为编码字符
		COMMON_API uint16_t byteToCode(const uint8_t* byteIn, uint8_t* codeOut, uint16_t nlenInput = 0);

		//将编码字符转换为字节序
		COMMON_API uint16_t codeToByte(const uint8_t* ocdeIn, uint8_t* byteOut);
	}

}


#endif