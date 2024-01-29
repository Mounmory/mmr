#include "CanRaffleState.h"
#include "RaffleActivity.h"
CanRaffleState::CanRaffleState(RaffleActivity* activity)
{
	//srand(time(NULL));
	this->activity = activity;
}

//已经扣除积分了，不能再扣了
void CanRaffleState::deductMeney() 
{
	cout << "已经扣过积分了" << endl;
}

//可以抽奖，根据抽奖情况改成新的状态
bool CanRaffleState::raffle()
{
	cout << "正在抽奖" << endl;
	int result = rand() % 10;
	if (0 == result)
	{
		//将activity的状态设置为发放奖品的状态
		activity->setState(activity->getDispenseState());
		return true;
	}
	else
	{
		cout << "很遗憾没有抽中奖品" << endl;
		//将activity的状态设置为不能抽奖的状态
		activity->setState(activity->getNoRaffleState());
		return false;
	}
}

void CanRaffleState::dispensePrize()
{
	cout << "没中奖，不能发放奖品" << endl;
}
