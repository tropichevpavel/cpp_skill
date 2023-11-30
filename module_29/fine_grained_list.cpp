
#include <iostream>
#include <mutex>
#include <shared_mutex>
#include <future>

std::shared_mutex cout_mutex;

struct Node
{
	int data;
	Node* next = nullptr;
	std::shared_mutex node_mutex;

	Node(const int& data) : data(data) {}
	~Node() { if (next) { next->node_mutex.lock(); delete next; } }
};

class FineGrainedQueue
{
	Node* head = nullptr;
	std::shared_mutex queue_mutex;
	std::mutex cout_mutex;

public:
	FineGrainedQueue() = default;

	void insert(const int& data, const int& pos = -1)
	{
		size_t counter = pos == -1 ? 1 : pos == 0 ? 0 : pos - 1;
		Node* cur;
		{
			{
				std::lock_guard<std::shared_mutex> tmp_lock(queue_mutex);
				if (!head)
				{
					head = new Node(data);
					return;
				}
				head->node_mutex.lock_shared();
				if (counter == 0)
				{
					cur = head;
					head = new Node(data);
					head->next = cur;
					cur->node_mutex.unlock_shared();
					return;
				}
			}

			cur = head;

			while (cur->next && (pos == -1 || --counter))
			{
				Node* prev = cur;
				cur->next->node_mutex.lock_shared();
				cur = cur->next;
				prev->node_mutex.unlock_shared();
			}
		}
		{
			cur->node_mutex.unlock_shared();
			std::lock_guard<std::shared_mutex> tmp_lock_node(cur->node_mutex);
			if (cur->next)
			{
				std::shared_lock<std::shared_mutex> tmp_lock(cur->next->node_mutex);
				Node* next = cur->next;
				cur->next = new Node(data);
				cur->next->next = next;
			}
			else cur->next = new Node(data);
		}
	}

	void print()
	{
		{
			std::lock_guard<std::shared_mutex> tmp_lock(queue_mutex);
			if (!head) return;
			head->node_mutex.lock_shared();
		}

		std::lock_guard<std::mutex> tmp_lock(cout_mutex);

		Node* cur = head;
		while (cur->next)
		{
			Node* prev = cur;
			cur->next->node_mutex.lock_shared();
			
			std::cout << " " << cur->data;
			cur = cur->next;

			prev->node_mutex.unlock_shared();
		}

		std::cout << " " << cur->data << std::endl;
		cur->node_mutex.unlock_shared();
	}

	auto size() -> size_t
	{
		{
			std::lock_guard<std::shared_mutex> tmp_lock(queue_mutex);
			if (!head) return 0;
			head->node_mutex.lock_shared();
		}

		size_t counter = 1;

		Node* cur = head;
		while (cur->next)
		{
			Node* prev = cur;
			cur->next->node_mutex.lock_shared();
			cur = cur->next;
			prev->node_mutex.unlock_shared();
			++counter;
		}
		cur->node_mutex.unlock_shared();
		return counter;
	}

	~FineGrainedQueue()
	{
		std::lock_guard<std::shared_mutex> tmp_lock(queue_mutex);
		if (head)
		{
			head->node_mutex.lock();
			delete head;
		}
	}
};

int main()
{
	FineGrainedQueue fgq;
	std::mutex cout_mutex;

	auto t1 = std::async(std::launch::async, [&fgq, &cout_mutex] ()
	{
		srand(7777);
		for (int i = 0; i < 10; ++i) fgq.insert(i);
		{
			std::lock_guard<std::mutex> tmp_lock(cout_mutex);
			std::cout << "Print from t1:" << std::endl;
			fgq.print();
		}
		fgq.insert(11, 6);
	});

	auto t2 = std::async(std::launch::async, [&fgq, &cout_mutex] ()
	{
		srand(8888);
		int r = rand() % 100;
		for (int i = 0; i < 10; ++i) fgq.insert(r + i);
		{
			std::lock_guard<std::mutex> tmp_lock(cout_mutex);
			std::cout << "Print from t2:" << std::endl;
			fgq.print();
		}
		fgq.insert(r + 10, 100);
	});

	auto t3 = std::async(std::launch::async, [&fgq, &cout_mutex] ()
	{
		srand(9999);
		int r = rand() % 1000;
		for (int i = 0; i < 10; ++i) fgq.insert(r + i, rand() % 10);
		{
			std::lock_guard<std::mutex> tmp_lock(cout_mutex);
			std::cout << "Print from t3:" << std::endl;
			fgq.print();
		}

		fgq.insert(r + 11, 1);
	});

	t1.wait();
	t2.wait();
	t3.wait();

	std::cout << "Print final: size - " << fgq.size() << std::endl;
	fgq.print();

	return 0;
}
