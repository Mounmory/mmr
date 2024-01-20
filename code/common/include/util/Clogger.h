#ifndef CLOGGER_H
#define CLOGGET_H
#include "Common.h"
#include "util/UtilCommon.h"


BEGINE_NAMESPACE(MmrCommon)

enum class emLogLevel
{
	LOG_OFF = -1,
	LOG_FORCE = 0,
	LOG_FATAL,
	LOG_ERROR,
	LOG_WARN,
	LOG_INFO,
	LOG_DEBUG
};


class COMMON_CLASS_API CLogger
{
public:
	CLogger();
	~CLogger();

private:

};


END_NAMESPACE(MmrCommon)

#endif