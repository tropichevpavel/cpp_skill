
#include <iostream>
#include <chrono>

struct Timer {
	inline static std::chrono::system_clock::time_point timeStart;
	static void start() { timeStart = std::chrono::system_clock::now(); }
	static double end() { return std::chrono::duration<double>(std::chrono::system_clock::now() - timeStart).count(); }
};

const int ARRAY_SIZE = 100'000;
const int TEST_COUNT = 1'000;

struct Data {
	int data[ARRAY_SIZE] = {};

	Data() = default;
	~Data() = default;

	void init() {
		srand(time(NULL));
		for (int i = 0; i < ARRAY_SIZE; ++i) data[i] = rand() % 10;
	}

	auto operator= (const Data& other) -> Data& {
		for (int i = 0; i < ARRAY_SIZE; ++i) data[i] = other.data[i];
		return *this;
	}
};

auto sum(const Data* d) -> uint64_t {
	uint64_t result = 0;

	for (int i = 0; i < ARRAY_SIZE; ++i)
		result += d->data[i];

	return result;
}

auto test(const Data* d) -> uint64_t {
	for (int i = 0; i < TEST_COUNT - 1; ++i) sum(d);
	return sum(d) / ARRAY_SIZE;
}

auto test(const Data d) -> uint64_t { return test(&d); }


int main() {

	// --- Stack
	Data data; data.init();
	std::cout << "Stack: " << std::endl;

	Timer::start();
	std::cout << "Avereng = " << test(data) << "\t Time: \t\t" << Timer::end() << std::endl;

	// --- Stack Ptr
	Timer::start();
	std::cout << "Avereng = " << test(&data) << "\t Ptr Time: \t" << Timer::end() << std::endl;


	// --- Heap
	Data* data2 = new Data(); data2->init(); // *data2 = data;
	std::cout << std::endl << "Heap: " << std::endl;

	Timer::start();
	std::cout << "Avereng = " << test(*data2) << "\t Time: \t\t" << Timer::end() << std::endl;

	// --- Heap Ptr
	Timer::start();
	std::cout << "Avereng = " << test(data2) << "\t Ptr Time: \t" << Timer::end() << std::endl;

	delete data2;

	return 0;
}
