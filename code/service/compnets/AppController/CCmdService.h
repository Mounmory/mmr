#ifndef CCMDSERVICE_H
#define CCMDSERVICE_H
#include "iservice/AppController/ICmdService.h"


class CCmdService : public ICmdService
{
public:
	CCmdService();
	~CCmdService();

	virtual void cmdLoop() override;
};

#endif // !CCMDSERVICE_H
