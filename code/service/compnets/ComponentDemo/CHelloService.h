﻿#ifndef CHELLOSERVICE_H
#define CHELLOSERVICE_H
#include "iservice/ComponentDemo/IHelloService.h"
#include <iostream>

class CHelloService :public IHelloService
{
public:
	CHelloService()
	{
		std::cout << "CHelloService construct!" << std::endl;
	}
	~CHelloService() 
	{
		std::cout << "CHelloService destruct!" << std::endl;
	}

	virtual void sayHello() override;
private:

};




#endif