#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include <Common_def.h>

class IComponent 
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual uint16_t  getIndex() = 0;

	virtual const char* getName() = 0;
	
	virtual bool initialise() = 0;

	virtual void terminate() = 0;
};


#endif