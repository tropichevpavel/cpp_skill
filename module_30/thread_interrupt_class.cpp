#include <thread>
#include <chrono>
#include <mutex>

thread_local bool thread_interrupt_flag = false;

class InterruptableThread
{
	std::mutex lock;
	bool* flag = nullptr;
	std::thread thread;

public:
	InterruptableThread(void (*task_func) ()) : thread(&InterruptableThread::start_func, this, task_func) {}

	~InterruptableThread() { thread.join(); }

	void interrupt()
	{
		std::lock_guard<std::mutex> tmp_lock(lock);
		if (flag) *flag = true;
	}

	void start_func(void (*task_func) ())
	{
		{
			std::lock_guard<std::mutex> tmp_lock(lock);
			flag = &thread_interrupt_flag;
		}
		task_func();
		{
			std::lock_guard<std::mutex> tmp_lock(lock);
			flag = nullptr;
		}
	}
		
	static bool checkInterrupted()
	{
		return thread_interrupt_flag;
	}
};

void thread_func()
{
	for(int i = 0; i < 100; ++i)
	{
		std::this_thread::sleep_for(std::chrono::seconds(1));
		if (InterruptableThread::checkInterrupted()) return;
	}
}

int main()
{
	InterruptableThread t(thread_func);
	std::this_thread::sleep_for(std::chrono::seconds(1));
	t.interrupt();
}
