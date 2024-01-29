#include "DispenseState.h"
#include "RaffleActivity.h"

DispenseState::DispenseState(RaffleActivity* activity)
{
	this->activity = activity;
}

void DispenseState::deductMeney()
{
	cout << "不能扣除积分" << endl;
}

bool DispenseState::raffle() 
{
	cout << "不能抽奖了" << endl;
	return false;
}

//发放奖品
void DispenseState::dispensePrize()
{
	if (activity->getCount() > 0)
	{
		cout << "送出奖品" << endl;
		activity->setState(activity->getNoRaffleState());
	}
	else
	{
		cout << "很遗憾,奖品发完了" << endl;
		//奖品已经发完，后面的人就不能抽奖了
		activity->setState(activity->getDispenseOutState());
	}
}
