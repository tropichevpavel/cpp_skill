#include <iostream>

// int main(const int argc, const char *argv[]) {

//     for (int i = 0; i < argc; i++) {
//         std::cout << argv[i] << std::endl;
//     }

//     return 0;
// }

int main(const int argc, const char *argv[]) {

	if (argc != 3) {
		std::cout << "Неверное кол-во аргументов " << std::endl;
		return 1;
	}

	if (*argv[1] == 'F')
		std::cout << "Temp F: " << ((9.0 * atof(argv[2]) / 5.0) + 32) << std::endl;

	else if (*argv[1] == 'C')
		std::cout << "Temp F: " << (((atof(argv[2]) * 5.0) - (5.0 * 32)) / 9) << std::endl;

	else {
		std::cout << "Неправильно заданы параметры";
		return 1;
	}

	return 0;
}