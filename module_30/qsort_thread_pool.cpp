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

	template<typename T, typename... Args>
	void push_task(T f, Args... args)
	{
		int queue_to_push = index++ % thread_count;
		task_type task = [=] { f(args...); };
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

	template<typename T, typename... Args>
	void push_request(T f, Args... args) { tpool.push_task(f, args...); }
};

RequestHandler tpool;

static bool make_thread_pool = true;
static bool make_thread = true;
constexpr size_t new_thread_bound = 100'000;

std::atomic<int> qsort_task_count = 0;

void quicksort(int* array, const size_t& left, const size_t& right, std::promise<void>* promise = nullptr)
{
	if (left >= right) return;

	if (promise && (right - left > new_thread_bound)) ++qsort_task_count;

	long left_bound = left;
	long right_bound = right;

	long middle = array[(left_bound + right_bound) / 2];

	do
	{
		while (array[left_bound] < middle) ++left_bound;
		while (array[right_bound] > middle) --right_bound;

		//Меняем элементы местами
		if (left_bound <= right_bound)
		{
			std::swap(array[left_bound], array[right_bound]);
			left_bound++;
			right_bound--;
		}
	}
	while (left_bound <= right_bound);

	if (make_thread_pool && (right_bound - left > new_thread_bound))
	{
		if (promise)
		{
			tpool.push_request(quicksort, array, left, right_bound, promise);
			quicksort(array, left_bound, right, promise);
		}
		else
		{
			auto promise = std::promise<void>();
			tpool.push_request(quicksort, array, left, right, &promise);
			quicksort(array, left_bound, right, &promise);
			promise.get_future().wait();
		}
	}
	else if (make_thread && (right_bound - left > new_thread_bound))
	{
		auto f = std::async(std::launch::async, [&] { quicksort(array, left, right_bound); });
		quicksort(array, left_bound, right);
	}
	else
	{
		quicksort(array, left, right_bound, promise);
		quicksort(array, left_bound, right, promise);
	}

	if (promise && (right - left > new_thread_bound) && !--qsort_task_count) promise->set_value();
}


bool is_sorted(const int* array, const size_t& size)
{
	for (size_t i = 0; i < size - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			std::cout << "Unsorted" << std::endl;
			return false;
		}
	}
	return true;
}


int main()
{
	srand(2468);
	size_t arr_size = 100'000'000;
	int* array = new int[arr_size];
	int* array2 = new int[arr_size];
	int* array3 = new int[arr_size];

	for (size_t i = 0; i < arr_size; ++i) array[i] = array2[i] = array3[i] = rand() % 500'000;

	// pool thread
	auto start = std::chrono::system_clock::now();
	quicksort(array, 0, arr_size);
	auto end = std::chrono::system_clock::now();

	printf("The time of PoolThread: %f seconds\n", ((std::chrono::duration<double>)(end - start)).count());
	is_sorted(array, arr_size);

	// async thread
	make_thread_pool = false;
	start = std::chrono::system_clock::now();
	quicksort(array2, 0, arr_size);
	end = std::chrono::system_clock::now();

	printf("The time of AsyncThread: %f seconds\n", ((std::chrono::duration<double>)(end - start)).count());
	is_sorted(array2, arr_size);

	// single thread
	make_thread = false;
	start = std::chrono::system_clock::now();
	quicksort(array3, 0, arr_size);
	end = std::chrono::system_clock::now();

	printf("The time of SingleThread: %f seconds\n", ((std::chrono::duration<double>)(end - start)).count());
	is_sorted(array3, arr_size);

	return 0;
}
