
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

static bool done = false;
std::queue<Part::PartPtr> shared_queue;
std::mutex lock_queue;
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
			std::lock_guard<std::mutex> raii_obj(lock_queue);
			shared_queue.push(Part::PartPtr(*parts.begin()));
			parts.remove(*parts.begin());
			locked_output("Part was added to queue");
		}
	}
	done = true;
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
			lock_queue.lock(); // блокируем мьютекс
			if(shared_queue.empty())
			{
				// если нет элементов, то освобождаем мьютекс и делаем задержку в 1 секунду перед следующий просыпанием
				lock_queue.unlock();
				if (done) break; // условие конца работы потока
				locked_output("second_thread useless check, queue is empty. Going to bed");
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				continue;
			}
			else
			{
				part_for_work = shared_queue.front(); // забираем элемент из очереди
				shared_queue.pop();
				lock_queue.unlock(); // не мешаем потоку А, освободим мьютекс
				locked_output("Part was removed from queue");
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
	std::thread ta(first_thread, std::ref(spare_parts));
	std::thread tb(second_thread);

	// ждем завершения
	ta.join();
	tb.join();

	locked_output("done");
	return 0;
}
