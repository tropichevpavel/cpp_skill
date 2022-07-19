
#include <iostream>

#define SIZE 10

class HashTable {
	int array[SIZE];
	int count = 0;

	int hash(int val) {
		return val;
	}

public:
	HashTable() {
		for (int i = 0; i < SIZE; ++i)
			array[i] = -1;
	}

	void add(int val) {
		array[hash(val)] = val;
		++count;
	}

	bool find(int val) {
		return array[hash(val)] == -1;
	}

	void del(int val) {
		if (find(val)) {
			array[hash(val)] = -1;
			--count;
		}
	}
};

int main() {

	HashTable ht;

	ht.add(1);
	ht.add(4);
	ht.add(3);
	ht.add(6);
	ht.add(5);
	ht.add(8);

	ht.del(1);

	std::cout << " -- find: str0 -> " << ht.find(1) << std::endl;
	std::cout << " -- find: str1 -> " << ht.find(5) << std::endl;
	std::cout << " -- find: str4 -> " << ht.find(8) << std::endl;

	return 0;
}
