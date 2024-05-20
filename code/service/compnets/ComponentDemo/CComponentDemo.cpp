#include "CComponentDemo.h"
#include "CCompFramework.h"
#include "CHelloService.h"

REGIST_COMPONENT(CComponentDemo);

CComponentDemo::CComponentDemo()
{
	
}

uint16_t CComponentDemo::getIndex()
{
	return 1;
}

const char* CComponentDemo::getName()
{
	static const char* szName = "ComponentDemo";
	return szName;
}

bool CComponentDemo::initialise(Json::Value& jsonConfig)
{
	std::shared_ptr<IHelloService> serPtr = std::make_shared<CHelloService>();
	CoreFrameworkIns->registService<IHelloService>(std::move(serPtr));


	m_pDemoHandler = std::make_shared<CHandlerDemo>();

	return true;
}

bool CComponentDemo::start()
{
	return true;
}

void CComponentDemo::stop()
{

}
