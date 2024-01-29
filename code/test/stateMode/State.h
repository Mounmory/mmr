#pragma once
class State
{
public:
	//扣除50积分
	virtual void deductMeney() = 0;

	//是否中奖
	virtual bool raffle() = 0;

	//发放奖品
	virtual void dispensePrize() = 0;
};

