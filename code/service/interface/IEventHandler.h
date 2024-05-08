#ifndef IEVENTHANDLER
#define IEVENTHANDLER
#include "util/CVarDatas.hpp"

class IEventHandler
{
public:
	IEventHandler() = default;
	virtual ~IEventHandler() = default;

	virtual void handleEvent(const std::string strTopic, const mmrUtil::CVarDatas& a_data) = 0;
};

#endif // !IEVENTHANDLER


