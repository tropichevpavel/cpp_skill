
#include <iostream>
#include <limits>
#include <iomanip>

const int ARRAY_SIZE = 100;

void compareDoubleTrue() {
	int errors = 0;
	double epsilon = std::numeric_limits<float>::epsilon(); // 0.0000000000001

	for (double d = 0; d < ARRAY_SIZE; ++d)
		for (int i = 0; i < ARRAY_SIZE; ++i)
			if (abs((d / i) * i - d) > epsilon) { 
				++errors;
				std::cout << std::setprecision(30) << "(" << d << " / " << i << ") * " << i << " = " << (d / i) * i << std::endl;
			}

	std::cout << " -- Errors: " << errors << std::endl
			  << " -- Epsilon: " << epsilon <<  std::endl;
}

void compareDouble() {
	int errors = 0;

	for (double d = 0; d < ARRAY_SIZE; ++d)
		for (int i = 1; i < ARRAY_SIZE; ++i)
			if ((d / i) * i != d) {
				++errors;
				std::cout << std::setprecision(30) << "(" << d << " / " << i << ") * " << i << " = " << (d / i) * i << std::endl;
			}

	std::cout << " -- Errors: " << errors << std::endl << std::endl;
}

int main() {
	compareDouble();
	std::cout << " --- --- --- --- --- --- " << std::endl << " True Compare" << std::endl;
	compareDoubleTrue();
	return 0;
}