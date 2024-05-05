#ifndef ITOOLBASE_H
#define ITOOLBASE_H
#include "Common_def.h"
#include <string>

BEGINE_NAMESPACE(MmrTools)

class IToolBase
{
public:
	IToolBase() = default;
	virtual ~IToolBase() = default;

	virtual const std::string getTypeName()const = 0;
};

END_NAMESPACE(MmrTools)

//获取PTCView对象指针
typedef MmrTools::IToolBase* (*getPluginService)();
//using getPluginInterface = std::function<MmrTools::IToolBase*()>;

#endif