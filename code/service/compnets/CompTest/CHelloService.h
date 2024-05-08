#ifndef CHELLOSERVICE_H
#define CHELLOSERVICE_H
//#include "CompTest/IHelloService.h"
#include "iservice/CompTest/IHelloService.h"

class CHelloService :public IHelloService
{
public:
	CHelloService() = default;
	~CHelloService() = default;

	virtual void sayHello() override;
private:

};




#endif