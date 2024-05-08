#include "CTestComponent.h"
#include "CCompFramework.h"
#include "CHelloService.h"

static CTestComponent* g_TestInstace = new CTestComponent;

CTestComponent::CTestComponent()
{
	CoreFrameworkIns->addComponent(this);
}

uint16_t CTestComponent::getIndex()
{
	return 1;
}

const char* CTestComponent::getName()
{
	static const char* szName = "helloComponent";
	return szName;
}

bool CTestComponent::initialise()
{
	CoreFrameworkIns->registService<IHelloService>(new CHelloService);

	return true;
}

void CTestComponent::terminate()
{

}
