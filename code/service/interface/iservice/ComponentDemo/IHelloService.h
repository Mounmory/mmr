#ifndef IHELLOSERVICE_H
#define IHELLOSERVICE_H

#include "Common_def.h"
#include "iservice/InterfaceCommon.h"
#include "util/UtilFunc.h"

class IHelloService
{
	//INTERFACE_GUID_DEFINE();
public:
	IHelloService() = default;
	virtual ~IHelloService() = default;

	virtual void sayHello() = 0;
};



#endif