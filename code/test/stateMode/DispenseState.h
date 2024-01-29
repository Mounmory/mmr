#pragma once
#include <iostream>
#include "State.h"

using namespace std;

class RaffleActivity;

//发放奖品的状态
class DispenseState :public State
{
public:
	DispenseState(RaffleActivity* activity);
	void deductMeney() override;
	bool raffle() override;
	//发放奖品
	void dispensePrize() override;

private:
	RaffleActivity* activity;
};
