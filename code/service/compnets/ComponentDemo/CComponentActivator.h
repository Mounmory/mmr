#ifndef CCOMPONENTACTIVATOR_H
#define CCOMPONENTACTIVATOR_H
#include "IComponent.h"
#include "CHandlerDemo.h"

class CComponentActivator :public IComponent 
{
public:
	CComponentActivator();
	virtual ~CComponentActivator() = default;

	virtual uint16_t  getIndex() override;

	virtual const char* getName() override;

	virtual bool initialise(const Json::Value& jsonConfig) override;

	virtual bool start() override;

	virtual void stop()override;

private:
	std::shared_ptr<CHandlerDemo> m_pDemoHandler;
};

#endif