
#include <iostream>

double fact(const double& n) {
	return n == 1 ? n : (n * fact(n - 1));
}

double fib(const double& n) {
	return n < 2 ? n : (fib(n - 1) + fib(n - 2));
}

double sum(const double& n) {
	return n == 1 ? n : (n + sum(n - 1));
}

int main() {
	std::cout << "Факториал: " << fact(5) << std::endl;
	std::cout << "Число фибаначи: " << fib(5) << std::endl << std::endl;

	std::cout << "Сумма: " << sum(5) << std::endl;

	return 0;
}