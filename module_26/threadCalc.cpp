
#include <iostream>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <ctime>

int main()
{
	auto startTime = std::chrono::system_clock::now();
	int arraySize, partSize, arraySum = 0;
	std::cout << "Input array size and part size (exp 20 60):" << std::endl;
	std::cin >> arraySize >> partSize;

	int partCount = std::ceil(arraySize / partSize);

	std::vector<int> array;
	int start = 0;
	int end = 99;
	for (int i = 0; i < arraySize; ++i) array.push_back(rand() % (end - start + 1) + start);
	// for (int i = 0; i < arraySize; ++i) std::cout << array[i] << std::endl;

	auto summFunc = [&arraySum](std::vector<int>* array, const int start, int count)
	{
		int sum = 0;

		while(count--)
		{
			if (array->size() > start + count) sum += (*array)[start + count];
		}

		arraySum += sum;
	};

	for (int i = 0; i < partCount; ++i)
	{
		std::thread t(summFunc, &array, i * partSize, partSize);
		t.join();
	}

	auto endTime = std::chrono::system_clock::now();
	std::cout << "Total sum: " << arraySum << std::endl;
	std::cout << "Time: " << ((std::chrono::duration<double>)(endTime - startTime)).count() << std::endl;

	return 0;
}
