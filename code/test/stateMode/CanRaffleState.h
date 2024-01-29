#pragma once
#include <iostream>
#include "State.h"
using namespace std;
class RaffleActivity;
//能抽奖状态
class CanRaffleState :public State
{
public:
	CanRaffleState(RaffleActivity* activity);
	//已经扣除积分了，不能再扣了
	void deductMeney() override;
	//可以抽奖，根据抽奖情况改成新的状态
	bool raffle() override;
	void dispensePrize() override;
private:
	RaffleActivity* activity;
};
