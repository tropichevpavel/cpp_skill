
#include <future>
#include <iostream>
#include <mutex>


std::mutex lock_add_thread;

size_t 	thread_count = 7,
		thread_count_cur = 0;

void merge(int* array, const int& left, const int& middle, const int& right)
{
	const int nl = middle - left + 1;
	const int nr = right - middle;

	// создаем временные массивы
	int* arr_left = new int[nl];
	int* arr_right = new int[nr];

	// копируем данные во временные массивы
	for (int i = 0; i < nl; i++) arr_left[i] = array[left + i];
	for (int j = 0; j < nr; j++) arr_right[j] = array[middle + 1 + j];

	int i = 0, j = 0;
	int k = left;  // начало левой части

	while (i < nl && j < nr)
	{
		// записываем минимальные элементы обратно во входной массив
		if (arr_left[i] <= arr_right[j])
		{
			array[k] = arr_left[i];
			i++;
		}
		else
		{
			array[k] = arr_right[j];
			j++;
		}
		k++;
	}
	// записываем оставшиеся элементы левой части
	while (i < nl)
	{
		array[k] = arr_left[i];
		i++;
		k++;
	}
	// записываем оставшиеся элементы правой части
	while (j < nr)
	{
		array[k] = arr_right[j];
		j++;
		k++;
	}

	delete [] arr_left;
	delete [] arr_right;
}

void merge_sort(int* array, const int& left, const int& right)
{
	if (left >= right) return;

	int middle = (left + right - 1) / 2;

	merge_sort(array, left, middle);
	merge_sort(array, middle + 1, right);
	merge(array, left, middle, right);
}

void merge_sort_thread(int* array, const int& left, const int& right)
{
	if (left >= right) return;

	int middle = (left + right - 1) / 2;

	std::future<void> future_left;
	std::future<void> future_right;

	lock_add_thread.lock();
	if (thread_count_cur < thread_count)
	{
		++thread_count_cur;
		lock_add_thread.unlock();
		future_left = std::async(std::launch::async, merge_sort_thread, array, left, middle);
	}
	else
	{
		lock_add_thread.unlock();
		merge_sort(array, left, middle);
	}

	lock_add_thread.lock();
	if (thread_count_cur < thread_count)
	{
		++thread_count_cur;
		lock_add_thread.unlock();
		future_right = std::async(std::launch::async, merge_sort_thread, array, middle + 1, right);		
	}
	else
	{
		lock_add_thread.unlock();
		merge_sort(array, middle + 1, right);
	}

	if (future_left.valid() && future_right.valid())
	{
		std::lock_guard<std::mutex> tmp_lock(lock_add_thread);
		--thread_count_cur;
	}

	if (future_left.valid()) future_left.wait();
	if (future_right.valid()) future_right.wait();

	merge(array, left, middle, right);

	if (future_left.valid() || future_right.valid())
	{
		std::lock_guard<std::mutex> tmp_lock(lock_add_thread);
		--thread_count_cur;
	}
}

int main(int argc, char* argv[])
{
	srand(0);
	size_t arr_size = 50000000;

	if (argc > 1)
	{
		for (int i = 1; i < argc; ++i)
		{
			if (!strcmp(argv[i], "-s"))
			{
				try { arr_size = std::stoi(argv[i + 1]); } catch (...) { std::cout << "Error '-s' value!" << std::endl; exit(1); }
				++i;
				continue;
			}

			if (!strcmp(argv[i], "-t"))
			{
				try { thread_count = std::stoi(argv[i + 1]) - 1; } catch (...) { std::cout << "Error '-t' value!" << std::endl; exit(1); }
				++i;
				continue;
			}
		}
	}

	int* array = new int[arr_size];

	for (long i = 0; i < arr_size; ++i) array[i] = rand() % 500000;

	// многопоточный запуск
	auto start = std::chrono::system_clock::now();
	merge_sort_thread(array, 0, arr_size);
	auto end = std::chrono::system_clock::now();

	printf("The time of MultiThreads: %f seconds\n", ((std::chrono::duration<double>)(end - start)).count());

	for (long i = 0; i < arr_size - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			std::cout << "Unsorted" << std::endl;
			break;
		}
	}

	// однопоточная проверка
	start = std::chrono::system_clock::now();
	merge_sort(array, 0, arr_size);
	end = std::chrono::system_clock::now();

	printf("The time of SingleThread: %f seconds\n", ((std::chrono::duration<double>)(end - start)).count());

	for (long i = 0; i < arr_size - 1; ++i)
	{
		if (array[i] > array[i + 1])
		{
			std::cout << "Unsorted" << std::endl;
			break;
		}
	}

	delete [] array;
	return 0;
}
