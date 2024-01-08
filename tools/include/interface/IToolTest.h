#ifndef ITOOLTEST_H
#define ITOOLTEST_H

#include "interface/IToolBase.hpp"

BEGINE_NAMESPACE(MmrTools)

class IToolTest :public IToolBase
{
public:
	IToolTest() = default;
	virtual ~IToolTest() = default;

	virtual void testHello() = 0;
};

END_NAMESPACE(MmrTools)

#endif