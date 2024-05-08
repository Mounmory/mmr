#ifndef UTILFUNC_H
#define UTILFUNC_H
#include "Common_def.h"
#include "util/UtilExport.h"
#include <string>
#include <string.h>


BEGINE_NAMESPACE(mmrUtil)

	//UTF-8转本地字符
	COMMON_FUN_API bool utf8ToLocalString(const std::string& strIn,std::string& strOut);

	//本地字符转UTF-8
	COMMON_FUN_API bool localStringToUtf8(const std::string& strIn, std::string& strOut);

	//字节序转换
	COMMON_FUN_API void byteTranslate(const uint8_t* inBuf, const uint16_t nLen, const uint8_t transFlag, uint8_t* outBuf);

	//将字节序转换为编码字符
	COMMON_FUN_API bool stringToCode(const std::string strIn, std::string& strOut);

	//将编码字符转换为字节序
	COMMON_FUN_API bool codeToString(const std::string strIn, std::string& strOut);

	COMMON_FUN_API bool GetAppPathAndName(std::string& filePath, std::string& exeName);

END_NAMESPACE(mmrUtil)
#endif