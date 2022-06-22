
#include "IntArr.h"

int main() {
	IntArr<int> array(10);

	for (int i = 0; i < 10; ++i)
		array[i] = i + 1;

	try {
		array.resize(8);
		array.resize(-37);

	} catch(std::length_error& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		array.insertBefore(5, 20);
		array.insertBefore(100, 20);

	} catch(std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		array.remove(3);
		array.remove(89);

	} catch(std::out_of_range& e) {
		std::cout << e.what() << std::endl;
	}

	array.insertAtEnd(30);
	array.insertAtStart(40);

	int find = 20;
	int index = array.find(find);
	if (index > -1)
		std::cout << "Item " << find << " at index " << index << std::endl;
	else
		std::cout << "Item " << find << " not found!" << std::endl;

	IntArr<double> array2 = array;

	try {
		array2.insertAtEnd(34.55);
		array2.insertAtStart(234.55);

		array2.remove(1);
		array2.remove(array2.size() - 2);

	} catch(std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::cout << "First Array:" << std::endl << array.join() << std::endl;
	std::cout << "Second Array:" << std::endl << array2.join() << std::endl;

	return 0;
}