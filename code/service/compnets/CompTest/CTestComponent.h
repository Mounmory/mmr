#ifndef CTESTCOMPONENT_H
#define CTESTCOMPONENT_H
#include "IComponent.h"

class CTestComponent :public IComponent 
{
public:
	CTestComponent();
	virtual ~CTestComponent() = default;

	virtual uint16_t  getIndex() override;

	virtual const char* getName() override;

	virtual bool initialise() override;

	virtual void terminate()override;
};

#endif