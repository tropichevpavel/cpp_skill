
#include <iostream>
#include "DynamicArray_2.cpp"

int main() {
	DynamicArray<int> array1(10);
	DynamicArray<int> array2(5);

	DynamicArray<int> array3 = std::move(array1);

	array2 = std::move(array1);

	

	return 0;
}
