#include <iostream>
#include <queue>
#include <future>
#include <condition_variable>
#include <vector>

template<class T>
class BlockedQueue
{
	std::mutex lock;
	std::queue<T> task_queue;
	std::condition_variable event_holder;

public:
	void push(T& item)
	{
		std::lock_guard<std::mutex> tmp_lock(lock);
		task_queue.push(item);
		event_holder.notify_one();
	}

	void pop(T& item)
	{
		std::unique_lock<std::mutex> queue_lock(lock);
		if (task_queue.empty())
		{
			event_holder.wait(queue_lock, [this] { return !task_queue.empty(); });
		}
		item = task_queue.front();
		task_queue.pop();
	}

	bool fast_pop(T& item)
	{
		std::lock_guard<std::mutex> tmp_lock(lock);
		if (task_queue.empty()) return false;
		item = task_queue.front();
		task_queue.pop();
		return true;
	}
};

typedef std::function<void()> task_type;
typedef void (*FuncType) (int, int);

class ThreadPool
{
	int index;
	int thread_count;
	std::vector<std::thread> threads;
	std::vector<BlockedQueue<task_type>> thread_queues;

public:
	ThreadPool() :
		thread_count(std::thread::hardware_concurrency() != 0 ? std::thread::hardware_concurrency() : 4),
		thread_queues(thread_count) {}

	void start()
	{
		for (int i = 0; i < thread_count; ++i)
		{
			threads.emplace_back(&ThreadPool::thread_func, this, i);
		}
	}

	void stop()
	{
		for (int i = 0; i < thread_count; ++i)
		{
			task_type empty_task;
			thread_queues[i].push(empty_task);
		}
		for (auto& t : threads) t.join();
	}

	void push_task(FuncType f, int id, int arg)
	{
		int queue_to_push = index++ % thread_count;
		task_type task = [=]{f(id, arg);};
		thread_queues[queue_to_push].push(task);
	}

	void thread_func(const int& qindex)
	{
		while (true)
		{
			task_type task_to_do;
			bool res;
			int i = 0;
			
			for (; i < thread_count; ++i)
			{
				res = thread_queues[(qindex + i) % thread_count].fast_pop(task_to_do);
				if (res) break;
			}

			if (!res)
			{
				thread_queues[qindex].pop(task_to_do);
			}
			else if (!task_to_do)
			{
				thread_queues[(qindex + i) % thread_count].push(task_to_do);
			}

			if (!task_to_do) return;

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
