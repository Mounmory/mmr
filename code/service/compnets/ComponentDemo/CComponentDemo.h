#ifndef CCOMPONENTDEMO_H
#define CCOMPONENTDEMO_H
#include "IComponent.h"
#include "util/json.hpp"
#include "CHandlerDemo.h"

class CComponentDemo :public IComponent 
{
public:
	CComponentDemo();
	virtual ~CComponentDemo() = default;

	virtual uint16_t  getIndex() override;

	virtual const char* getName() override;

	virtual bool initialise(Json::Value& jsonConfig ) override;

	virtual bool start() override;

	virtual void stop()override;

private:
	std::shared_ptr<CHandlerDemo> m_pDemoHandler;
};

#endif