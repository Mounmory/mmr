#ifndef IHELLOSERVICE_H
#define IHELLOSERVICE_H

class IHelloService
{
public:
	IHelloService() = default;
	virtual ~IHelloService() = default;

	virtual void sayHello() = 0;

};



#endif