
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>

int main()
{
	int arraySize, partCount, arraySum = 0;
	std::cout << "Input array size and thread count (exp 200 10):" << std::endl;
	std::cin >> arraySize >> partCount;

	int partSize = std::ceil(arraySize / partCount);

	std::vector<int> array;
	int start = 0;
	int end = 99;
	for (int i = 0; i < arraySize; ++i) array.push_back(rand() % (end - start + 1) + start);

	auto summFunc = [](const std::vector<int>* array, const int partNum, int count, std::vector<int>* result)
	{
		int sum = 0;
		int start = partNum * count;

		while(count--)
		{
			if (array->size() > start + count) sum += (*array)[start + count];
		}

		result->push_back(sum);
	};

	std::vector<int> result;
	std::vector<std::thread> threads;

	auto startTime = std::chrono::system_clock::now();

	for (int i = 0; i < partCount; ++i)
	{
		threads.push_back(std::thread(summFunc, &array, i, partSize, &result));
	}

	for (auto& t : threads) t.join();

	for (int i = 0; i < partCount; ++i) arraySum += result[i];

	auto endTime = std::chrono::system_clock::now();
	std::cout << "Total sum: " << arraySum << std::endl;
	std::cout << "Time sum: " << ((std::chrono::duration<double>)(endTime - startTime)).count() << std::endl;

	std::cout << "Check summ: " << ([&result](){ int sum = 0; for (auto& val : result) sum += val; return sum; })() << std::endl;

	return 0;
}
