
#include <iostream>
#include "calculate.h"

int main() {
	double x = 0, y = 0;
	char operation;

	while (true) {
		std::cout << "Введите операцию ( + , - , *, / , ! , ^ ), для выхода q:" << std::endl;
		std::cin >> operation;

		if (operation == 'q') break;
		
		else if (!(operation == '+' || operation == '-' || operation == '*' || operation == '/' ||
				 operation == '!' || operation == '^')) {

			std::cout << "Введена неправельная операция!" << std::endl;
			continue;
		}

		if (operation == '!') {
			std::cout << "Введите число:" << std::endl;
			std::cin >> x;
			std::cout << x << "! = " << fact(x) << std::endl;

		} else {
			std::cout << "Введите последовательно 2 числа через Enter:" << std::endl;
			std::cin >> x >> y;

			std::cout << "Результат " << x << " " << operation << " " << y << " = ";

			if (operation == '+') std::cout << plus(x, y);

			else if (operation == '-') std::cout << minus(x, y);
				
			else if (operation == '*')	std::cout << multy(x, y);

			else if (operation == '/')
				if (y) std::cout << div(x, y);
				else std::cout << "На ноль делить нельзя!";
			
			else
				std::cout << expon(x, y);

			std::cout << std::endl << std::endl;
		}

		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}

	return 0;
}
