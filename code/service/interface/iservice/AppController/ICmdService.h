#ifndef ICMDSERVICE_H
#define ICMDSERVICE_H

#include "Common_def.h"
#include "iservice/InterfaceCommon.h"

class ICmdService
{
	//INTERFACE_GUID_DEFINE();
public:
	ICmdService() = default;
	virtual ~ICmdService() = default;

	virtual void cmdLoop() = 0;
};


#endif // !ICMDSERVICE
