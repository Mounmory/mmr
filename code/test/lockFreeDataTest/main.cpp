#include <iostream>
#include "Common_def.h"
#include "util/CLockFreeStack.hpp"

#include <memory>
#include <set>
#include <condition_variable>
#include <mutex>
#include <thread>

CLockFreeStack<int> g_stack;
std::mutex g_mt;
std::condition_variable g_cv;


void pushStack(int bg,int ed) 
{
	//std::unique_lock<std::mutex> lock(g_mt);
	//std::cout << "pushStack wait notify..." << std::endl;
	//g_cv.wait(lock);
	std::cout << "pushStack go..." << std::endl;

	for (int i = bg; i < ed; ++i)
	{
		g_stack.push(i);
	}
	std::cout << "pushStack push end..." << std::endl;
	for (int i = bg; i < ed-5; ++i)
	{
		g_stack.pop();
	}
	std::cout << "pushStack pop end..." << std::endl;
}


int main(int argc, char **argv)
{
	//std::thread td1(pushStack,0,100000000);
	//std::thread td2(pushStack,100000001,200000000);
	//std::thread td3(pushStack, 200000001, 300000000);
	//std::thread td4(pushStack, 300000001, 400000000);

	std::thread td1(pushStack, 0, 10000);
	std::thread td2(pushStack, 10001, 20000);
	std::thread td3(pushStack, 20001, 30000);
	std::thread td4(pushStack, 30001, 40000);

	//std::this_thread::sleep_for(std::chrono::seconds(1));
	//std::cout << "before notify..." << std::endl;
	//g_cv.notify_all();
	//std::cout << "after notify..." << std::endl;

	td1.join();
	td2.join();
	td3.join();
	td4.join();

	auto data = g_stack.pop();
	while (data)
	{
		std::cout << *data << std::endl;
		data = g_stack.pop();
	}


	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();

	return 0;
}
