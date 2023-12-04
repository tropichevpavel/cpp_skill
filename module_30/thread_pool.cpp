#include <iostream>
#include <queue>
#include <future>
#include <condition_variable>
#include <vector>

#define THREAD_POOL_COUNT 4

typedef std::function<void()> task_type;
typedef void (*FuncType) (int, int);

class ThreadPool
{
	std::vector<std::thread> threads;
	std::mutex lock;
	std::queue<task_type> task_queue;
	std::condition_variable event_holder;
	volatile bool is_work;

public:
	void start()
	{
		is_work = true;
		for (int i = 0; i < THREAD_POOL_COUNT; ++i)
		{
			threads.push_back(std::thread(&ThreadPool::thread_func, this));
		}
	}

	void stop()
	{
		is_work = false;
		event_holder.notify_all();
		for (auto& t : threads) t.join();
	}

	void push_task(FuncType f, int id, int arg)
	{
		std::lock_guard<std::mutex> tmp_lock(lock);
		task_queue.push([=] { f(id, arg); });
		event_holder.notify_one();
	}

	void thread_func()
	{
		while (true)
		{
			task_type task_to_do;
			{
				std::unique_lock<std::mutex> th_lock(lock);
				if (task_queue.empty() && !is_work) return;
				if (task_queue.empty())
				{
					event_holder.wait(th_lock, [this] { return !task_queue.empty() || !is_work; });
				}
				if (!task_queue.empty())
				{
					task_to_do = task_queue.front();
					task_queue.pop();
				}
			}
			task_to_do();
		}
	}
};

class RequestHandler
{
	ThreadPool tpool;

public:
	RequestHandler() { tpool.start(); }
	~RequestHandler() { tpool.stop(); }

	void push_request(FuncType f, int id, int arg) { tpool.push_task(f, id, arg); }
};

std::mutex cout_lock;

void task_func(int id, int delay)
{
	std::this_thread::sleep_for(std::chrono::seconds(delay));
	std::lock_guard<std::mutex> tmp_lock(cout_lock);
	std::cout << "task " << id << " made by thread_id " << std::this_thread::get_id() << std::endl;
}

int main()
{
	srand(2468);
	RequestHandler rh;
	for (int i = 0; i < 20; ++i) rh.push_request(task_func, i, 1 + rand() % 4);
	return 0;
}
