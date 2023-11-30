
#include <thread>
#include <iostream>
#include <atomic>
#include <vector>

std::atomic<int> sum = 0;

void summ(const std::vector<int>& arr, const int& start, const int& end)
{
	int local_sum = 0;
	for (int i = start; i < end; ++i) local_sum += arr[i];
	sum += local_sum;
}

int main()
{
	std::vector<int> arr;
	size_t arr_size = 10000000;
	for (int i = 0; i < arr_size; ++i) arr.push_back(i);

	auto t1 = std::thread(summ, std::ref(arr), 10, 140);
	auto t2 = std::thread(summ, std::ref(arr), 500, 9000);
	auto t3 = std::thread(summ, std::ref(arr), 95888, 9589999);

	t1.join();
	t2.join();
	t3.join();

	std::cout << sum << std::endl;

	return 0;
}
