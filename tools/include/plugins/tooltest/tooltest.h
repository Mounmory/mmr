#ifndef TOOLTEST_H
#define TOOLTEST_H

#include "Common.h"
#include "interface/IToolTest.h"

BEGINE_NAMESPACE(MmrTools)

class tooltest :public IToolTest
{
public:
	tooltest();
	~tooltest();

	virtual const std::string getTypeName()const override;

	virtual void testHello() override;
};

END_NAMESPACE(MmrTools)
#endif