#pragma once
#include "CanRaffleState.h"
#include "DispenseOutState.h"
#include "DispenseState.h"
#include "State.h"
#include "NoRaffleState.h"

class RaffleActivity
{
public:
	State* getState() const{
		return state;
	}
	void setState(State* const state)
	{
		this->state = state;
	}

	int getCount()
	{
		return count--;
	}

	void setCount(const int count)
	{
		this->count = count;
	}

	State* getNoRaffleState() const
	{
		return noRaffleState;
	}

	void setNoRaffleState(State* const noRaffleState)
	{
		this->noRaffleState = noRaffleState;
	}

	State* getCanRaffleState() const
	{
		return canRaffleState;
	}

	void setCanRaffleState(State* const canRaffleState)
	{
		this->canRaffleState = canRaffleState;
	}

	State* getDispenseState() const
	{
		return dispenseState;
	}

	void setDispenseState(State* const dispenseState)
	{
		this->dispenseState = dispenseState;
	}

	State* getDispenseOutState() const
	{
		return dispenseOutState;
	}

	void setDispenseOutState(State* const dispenseOutState)
	{
		this->dispenseOutState = dispenseOutState;
	}

	RaffleActivity(int count)
	{
		//初始化当前状态为 不能抽奖状态
		this->state = getNoRaffleState();
		//初始化奖品数量
		this->count = count;
	}

	//扣分，调用当前状态的deductMoney
	void deductMoney()
	{
		state->deductMeney();
	}

	//抽奖
	void raffle()
	{
		//如果抽中奖了，则领奖品
		if (state->raffle())
		{
			state->dispensePrize();
		}
	}

private:
	//state表示活动当前的状态
	State* state = nullptr;
	//奖品数量
	int count = 0;
	//四个属性 表示四种状态
	State* noRaffleState = new NoRaffleState(this);
	State* canRaffleState = new CanRaffleState(this);
	State* dispenseState = new DispenseState(this);
	State* dispenseOutState = new DispenseOutState(this);
};
