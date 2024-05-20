#ifndef ICOMPONENT_H
#define ICOMPONENT_H
#include <Common_def.h>
#include "util/json.hpp"

class IComponent 
{
public:
	IComponent() = default;
	virtual ~IComponent() = default;

	virtual uint16_t  getIndex() = 0;

	virtual const char* getName() = 0;
	
	virtual bool initialise(Json::Value& jsonConfig) = 0;

	virtual bool start() = 0;

	virtual void stop() = 0;
};


#endif