
#include <iostream>

// 1 на рассмотрении
void show(const int& a) {
	std::cout << "Значение а - " << a << std::endl;
}

// 2 на рассмотрении
template<typename T> void show(T a) {
	std::cout << "Значение а - " << a << std::endl;
}

// 4 на рассмотрении
template<typename T1, typename T2> void show2(T1 a, T2 b) {
	std::cout << "Значение а - " << a << std::endl;
	std::cout << "Значение b - " << b << std::endl;
}

// 3 на рассмотрении
template<> void show2(const int& a, const int& b) {
	std::cout << "Значение а - " << a << std::endl;
	std::cout << "Значение b - " << b << std::endl;
	std::cout << "Сумма - " << a + b << std::endl;
}

// не все типы могут выступать в качестве аргумента b
template<typename T> void show2(T a, const int& b) {
	std::cout << "Значение а - " << a << std::endl;
	std::cout << "Значение b - " << b << std::endl;
}


template<typename T> class SomeClass {

	T _value;

public:
	SomeClass(T value) : _value(value) {};
	~SomeClass() = default;

	void show() {
		std::cout << "Value = " << _value << std::endl;
	}
};

template<> class SomeClass<int> {

	int _value;

public:
	SomeClass(int value) : _value(value) {};
	~SomeClass() = default;

	void show() {
		std::cout << "Int Value = " << _value << std::endl;
	}
};

template<typename T = int> class SomeClass2 {

	T _value;

public:
	SomeClass2(T value) : _value(value) {};
	~SomeClass2() = default;

	void show() {
		std::cout << "Value = " << _value << std::endl;
	}
};

template<typename T, const int size> class Array {

	T _data[size];
	int _size;

public:
	Array() : _size(size) {
		for (int i = 0; i < size; i++) _data[i] = (T)(i * i);
	};
	~Array() = default;

	void show() {
		std::cout << join() << std::endl;
	}

	std::string join(const char* sep = ", ") const {
		std::string join = "";

		for (int i = 0; i < _size; ++i)
			join += std::to_string(_data[i]) + (i == _size - 1 ? "" : sep);

		return join;
	}
};

auto sss(const int i) {
	return 4 * i;
}

void sss2() {}

template<typename T, typename ... Args> void sss2(T val, Args ... args) {
	std::cout << "Value - " << val << std::endl;
	sss2(args ...);
}

template<typename T, typename ... Args> void show(T value, Args ... args)
{
    std::cout << value << ", ";
    show(args ...);
}


auto wwmain() -> int {
	// show2(5, 12.5);

	// show<double>(12.5);
	// show<std::string>("hello one12");

	// SomeClass<int> a(5);
	// a.show();

	// SomeClass<char*> b("abl");
	// b.show();

	// SomeClass2<> c(10);
	// c.show();

	// SomeClass2<std::string> d("one is d");
	// d.show();

	Array<int, 10> array;
	array.show();

	std::cout << "out - " << typeid(array).name() << std::endl;

	std::cout << "out - " << sss(10) << std::endl;

	sss2(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
	// show(1, 2, 3, 4, 5, 6, 7, 8, 9, 0);

	return 0;
}
