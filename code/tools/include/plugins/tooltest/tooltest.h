#ifndef TOOLTEST_H
#define TOOLTEST_H

#include "Common_def.h"
#include "PluginCommon.h"
#include "interface/IToolTest.h"


BEGINE_NAMESPACE(MmrTools)

class tooltest :public IToolTest
{
	PLUGIN_INTERFACE_NAME(MmrTools::IToolTest)
public:
	tooltest();
	~tooltest();

	virtual void testHello() override;
};

END_NAMESPACE(MmrTools)

PLUGIN_REGISTER_FUNC(MmrTools::tooltest)
#endif