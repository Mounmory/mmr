#include "DispenseOutState.h"
#include "RaffleActivity.h"

DispenseOutState::DispenseOutState(RaffleActivity* activity)
{
	this->activity = activity;
}

void DispenseOutState::deductMeney()
{
	cout << "奖品已经发完了，请下次再参加" << endl;
}

bool DispenseOutState::raffle()
{
	cout << "奖品已经发完了，请下次再参加" << endl;
	return false;
}

//发放奖品
void DispenseOutState::dispensePrize()
{
	cout << "奖品已经发完了，请下次再参加" << endl;
}
