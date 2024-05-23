#include "CComponentActivator.h"
#include "CCompFramework.h"
#include "CHelloService.h"

REGIST_COMPONENT(CComponentActivator);

CComponentActivator::CComponentActivator()
{
	
}

uint16_t CComponentActivator::getIndex()
{
	return 0;
}

const char* CComponentActivator::getName()
{
	static const char* szName = "ComponentDemo";
	return szName;
}

bool CComponentActivator::initialise(const Json::Value& jsonConfig)
{
	std::shared_ptr<IHelloService> serPtr = std::make_shared<CHelloService>();
	CoreFrameworkIns->registService<IHelloService>(std::move(serPtr));


	m_pDemoHandler = std::make_shared<CHandlerDemo>();

	return true;
}

bool CComponentActivator::start()
{
	return true;
}

void CComponentActivator::stop()
{

}
