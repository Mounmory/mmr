#include "CComponentActivator.h"
#include "CCmdService.h"



REGIST_COMPONENT(CComponentActivator);

CComponentActivator::CComponentActivator()
{
	
}

uint16_t CComponentActivator::getIndex()
{
	return 1;
}

const char* CComponentActivator::getName()
{
	static const char* szName = "AppController";
	return szName;
}

bool CComponentActivator::initialise(const Json::Value& jsonConfig)
{
	std::shared_ptr<ICmdService> serPtr = std::make_shared<CCmdService>();
	CoreFrameworkIns->registService<ICmdService>(std::move(serPtr));


	return true;
}

bool CComponentActivator::start()
{
	return true;
}

void CComponentActivator::stop()
{

}
