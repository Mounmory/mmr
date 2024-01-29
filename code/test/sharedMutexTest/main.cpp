#include "Common.h"
#include <iostream>
#ifdef OS_WIN
#include <shared_mutex>//C++17支持
#endif
#include <thread>

#ifdef OS_WIN
std::shared_mutex mutex;
int shared_data = 0;
#endif

void read_data() 
{
#ifdef OS_WIN
	PRINT_LOG("read data begin!");
	std::shared_lock<std::shared_mutex> lock(mutex);
	PRINT_LOG("read data after lock!");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	PRINT_LOG("Read data: " << shared_data);
#endif
}

void write_data() {
#ifdef OS_WIN
	PRINT_LOG("write data begin!" );
	std::unique_lock<std::shared_mutex> lock(mutex);
	PRINT_LOG("write data after lock!" );
	shared_data++;
	PRINT_LOG("Write data: " << shared_data );
#endif
}


void try_read_data()
{
#ifdef OS_WIN
	PRINT_LOG("read data begin!");
	if ( false == mutex.try_lock_shared())
	{
		PRINT_LOG("read data try lock failed!");
		return;
	}
	//std::shared_lock<std::shared_mutex> lock(mutex);
	PRINT_LOG("read data after lock!");
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	PRINT_LOG("Read data: " << shared_data);
	mutex.unlock_shared();
#endif
}

void try_write_data() 
{
#ifdef OS_WIN
	PRINT_LOG("write data begin!");
	if (false == mutex.try_lock())
	{
		PRINT_LOG("write data try lock failed!");
		return;
	}
	//std::unique_lock<std::shared_mutex> lock(mutex);
	PRINT_LOG("write data after lock!");
	shared_data++;
	PRINT_LOG("Write data: " << shared_data);
	mutex.unlock();
#endif
}

void test1() 
{
	std::thread t1(read_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t2(read_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t3(write_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t4(read_data);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
}

void test2_try_lock()
{
	std::thread t1(try_read_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t2(try_read_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t3(try_write_data);
	std::this_thread::sleep_for(std::chrono::milliseconds(50));
	std::thread t4(try_read_data);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	std::cout << "输入任意字符继续..." << std::endl;
	std::cin.get();
}

int main() {
	test1();
	test2_try_lock();
	return 0;
}
