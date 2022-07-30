
#include <iostream>

// ---- Fibonacci Struct ---- //

template<int n>
struct Fibonacci {
	static constexpr int value = Fibonacci<n - 1>::value + Fibonacci<n - 2>::value;
};

template<>
struct Fibonacci<0> {
	static constexpr int value = 0;
};

template<>
struct Fibonacci<1> {
	static constexpr int value = 1;
};

// ---- Fibonacci Func---- //

template<int n>
int factorial() {
	return n * factorial<n - 1>();
}

template<>
int factorial<1>() {
	return 1;
}


int main() {
	std::cout << " - Fibonacci (30) = " << Fibonacci<30>::value << std::endl;
	std::cout << " - Factorial (30) = " << factorial<30>() << std::endl;
	return 0;
}
