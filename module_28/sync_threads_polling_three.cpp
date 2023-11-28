
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <list>
#include <thread>

typedef struct Part
{
	int part_id;
	float volume;
	typedef std::shared_ptr<struct Part> PartPtr;
}
Part;

static bool done_first = false;
static bool done_second = false;
std::queue<Part::PartPtr> shared_queue_for_second;
std::queue<Part::PartPtr> shared_queue_for_third;
std::mutex lock_queue_for_second;
std::mutex lock_queue_for_third;
std::mutex lock_cout;

void locked_output(const std::string &str)
{
	// захват мьютекса для защищенного вывода
	std::lock_guard<std::mutex> raii(lock_cout);
	std::cout << str << std::endl;
}

void first_thread_work(Part::PartPtr& part)
{
	// делаем вычитание из объема и имитируем задержку
	part->volume -= 2;
	std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 6000));

	locked_output("first_thread_work finished with part " + std::to_string(part->part_id));
}

void first_thread(std::list<Part::PartPtr>& parts)
{
	srand(7777777);
	const size_t size = parts.size();
	for (size_t i = 0; i < size; ++i)
	{
		first_thread_work(*parts.begin()); // обрабатываем деталь
		// кладём в очередь
		{
			std::lock_guard<std::mutex> raii_obj(lock_queue_for_second);
			shared_queue_for_second.push(Part::PartPtr(*parts.begin()));
			locked_output("Part " + std::to_string((*parts.begin())->part_id) + " was added to queue_for_second");
			parts.remove(*parts.begin());
		}
	}
	done_first = true;
}

void second_thread_work(Part::PartPtr& part)
{
	// делаем вычитание из объема и имитируем задержку
	part->volume -= 2;
	std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 6000));

	locked_output("second_thread_work finished with part " + std::to_string(part->part_id));
}

void second_thread()
{
	srand(100000);
	while (true)
	{
		Part::PartPtr part_for_work;
		{
			lock_queue_for_second.lock(); // блокируем мьютекс
			if(shared_queue_for_second.empty())
			{
				// если нет элементов, то освобождаем мьютекс и делаем задержку в 1 секунду перед следующий просыпанием
				lock_queue_for_second.unlock();
				if (done_first) break; // условие конца работы потока
				locked_output("second_thread useless check, queue is empty. Going to bed");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				continue;
			}
			else
			{
				part_for_work = shared_queue_for_second.front(); // забираем элемент из очереди
				shared_queue_for_second.pop();
				lock_queue_for_second.unlock(); // не мешаем потоку А, освободим мьютекс
				locked_output("Part " + std::to_string(part_for_work->part_id) + " was removed from queue_for_second");
			}
		}

		second_thread_work(part_for_work); // работаем над деталью
		// кладём в очередь
		{
			std::lock_guard<std::mutex> raii_obj(lock_queue_for_third);
			shared_queue_for_third.push(part_for_work);
			locked_output("Part " + std::to_string(part_for_work->part_id) + " was added to queue_for_third");
		}
	}

	done_second = true;
}

void third_thread_work(Part::PartPtr& part)
{
	// делаем вычитание из объема и имитируем задержку
	part->volume -= 2;
	std::this_thread::sleep_for(std::chrono::milliseconds(500 + rand() % 6000));

	locked_output("third_thread_work finished with part " + std::to_string(part->part_id));
}

void third_thread()
{
	srand(88778844);
	while (true)
	{
		Part::PartPtr part_for_work;
		{
			lock_queue_for_third.lock(); // блокируем мьютекс
			if(shared_queue_for_third.empty())
			{
				// если нет элементов, то освобождаем мьютекс и делаем задержку в 1 секунду перед следующий просыпанием
				lock_queue_for_third.unlock();
				if (done_second) break; // условие конца работы потока
				locked_output("third_thread useless check, queue is empty. Going to bed");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				continue;
			}
			else
			{
				part_for_work = shared_queue_for_third.front(); // забираем элемент из очереди
				shared_queue_for_third.pop();
				lock_queue_for_third.unlock(); // не мешаем потоку А, освободим мьютекс
				locked_output("Part " + std::to_string(part_for_work->part_id) + " was removed from queue_for_third");
			}
		}

		second_thread_work(part_for_work); // работаем над деталью
	}
}

int main()
{
	std::list<Part::PartPtr> spare_parts;
	for (int i = 0; i < 5; ++i) spare_parts.push_back(Part::PartPtr(new Part{ i + 1, 10.0 }));

	// запуск потоков
	std::thread t1(first_thread, std::ref(spare_parts));
	std::thread t2(second_thread);
	std::thread t3(third_thread);

	// ждем завершения
	t1.join();
	t2.join();
	t3.join();

	locked_output("done");
	return 0;
}
