
#include <fstream>
#include <iostream>
#include <string>

void read(const std::string& file) {
	std::ifstream fromFile(file);

	if (!fromFile.is_open()) {
		std::cout << "Cant open the file" << std::endl;
		return;
	}

	int number;
	if (fromFile >> number)
		std::cout << "The num is : " << number << std::endl;
	fromFile.close();
}

void write(const std::string& file, const std::string& data) {
	std::ofstream toFile(file);
	toFile << data;
	toFile.close();
}

void writeExtend(const std::string& file, const std::string& data) {
	std::ofstream toFile(file);
	toFile << data;

	toFile.seekp(0, std::ios_base::beg);
	toFile << "111";

	toFile.seekp(2);
	toFile << "888";

	toFile.seekp(0, std::ios_base::end);
	toFile << "000";

	toFile.close();
}

int main() {
	std::string fileName = "text.txt";

	write(fileName, "4");
	read(fileName);
	write(fileName, "456");
	read(fileName);
	writeExtend(fileName, "9864");
	read(fileName);

	return 0;
}
