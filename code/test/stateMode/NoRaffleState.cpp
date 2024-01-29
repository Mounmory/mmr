#include "NoRaffleState.h"
#include "RaffleActivity.h"

NoRaffleState::NoRaffleState(RaffleActivity* activity)
{
	this->activity = activity;
}

//在不能抽奖状态是可以扣积分的，扣除积分后设置成可以抽奖状态
void NoRaffleState::deductMeney()
{
	std::cout << "扣除50积分，可以抽奖了" << endl;
	activity->setState(activity->getCanRaffleState());
}

bool NoRaffleState::raffle()
{
	cout << "扣了积分才能抽奖" << endl;
	return false;
}

void NoRaffleState::dispensePrize()
{
	cout << "不能发奖品" << endl;
}
