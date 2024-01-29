#include "Common.h"

#include <iostream>
#include "RaffleActivity.h"
using namespace std;
int main(int argc, char* argv[])
{
	RaffleActivity* activity = new RaffleActivity(1);

	for(int i=0;i<50;i++)
	{
		cout << "第" << i << "次抽奖" << endl;
		activity->deductMoney();
		activity->raffle();
		cout << endl;
	}
	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
	return 0;
}
