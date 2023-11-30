
#include <thread>
#include <iostream>
#include <atomic>

struct Spinlock
{
	std::atomic<bool> _lock = false;

	void lock() { while (_lock.exchange(true)); }

	void unlock() { _lock.store(false); }
};

Spinlock spinlock;
static int counter = 0;

void add()
{
	for (int i = 0; i < 100000000; i++)
	{
		spinlock.lock();
		std::this_thread::sleep_for(std::chrono::seconds(3)); // нагрузка на процессор
		counter++;
		spinlock.unlock();
	}
}

void subtraction()
{
	for (int i = 0; i < 100000000; i++)
	{
		spinlock.lock();
		std::this_thread::sleep_for(std::chrono::seconds(3)); // нагрузка на процессор
		counter--;
		spinlock.unlock();
	}
}

int main()
{
	std::thread th1(add);
	std::thread th2(subtraction);

	th1.join();
	th2.join();

	std::cout << counter << std::endl;

	return 0;
}
