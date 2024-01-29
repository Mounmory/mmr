#pragma once
#include "State.h"
class RaffleActivity;
//奖品发送完毕状态
class DispenseOutState :public State
{
public:
	DispenseOutState(RaffleActivity* activity);
	void deductMeney() override;
	bool raffle() override;
	//发放奖品
	void dispensePrize() override;

private:
	RaffleActivity* activity;
};
