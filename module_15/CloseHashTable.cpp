
#include <iostream>
#include <string>

typedef std::string Key;

class CloseHashTable {
	enum PairStatus {
		free,
		engaged,
		deleted
	};

	struct Pair {
		Key key = "";
		int value = -1;
		PairStatus status = PairStatus::free;

		Pair() = default;
		Pair(Key key, int value) : key(key), value(value), status(PairStatus::engaged) {}

		Pair& operator = (const Pair& other) {
			key = other.key;
			value = other.value;
			status = other.status;
			return *this;
		}
	};

	int memSize = 8;
	int count = 0;
	Pair* data;

public:
	CloseHashTable() { data = new Pair[memSize]; }

	void add(Key key, int value) {
		int index = -1, i = 0;
		for (; i < memSize; ++i)
			if (data[index = hash(key, i)].status != PairStatus::engaged)
				break;

		if (i >= memSize) {
			resize();
			add(key, value);
			return;
		}

		data[index] = Pair(key, value);
		++count;
	}

	int find(Key key) {
		int index = 0, i = 0;
		for (; i < memSize; ++i)
			if (data[index = hash(key, i)].status == PairStatus::engaged && data[index].key == key) return data[index].value;
			else if (data[index].status == PairStatus::free) return -1;
		return -1;
	}

	void del(Key key) {
		int index = 0, i = 0;
		for (; i < memSize; ++i)
			if (data[index = hash(key, i)].status == PairStatus::engaged && data[index].key == key) data[index].status = PairStatus::deleted;
			else if (data[index].status == PairStatus::free) break;
	}

	void resize() {
		Pair* oldData = data;
		int oldMemSizee = memSize;

		memSize *= 2;
		count = 0;

		data = new Pair[memSize];
		for (int i = 0; i < memSize; ++i)
			if (oldData[i].status == PairStatus::engaged)
				add(oldData[i].key, oldData[i].value);

		delete[] oldData;
	}

	~CloseHashTable() { delete[] data; }

private:
	int hash(Key key, int offset = 0) {
		int sum = 0;
		for (const auto& ch : key) sum += ch;
		return (sum % memSize + offset * (sum % memSize + offset * 2)) % memSize; // двойное хеширование // квадратное - (sum % memSize + offset * offset) % memSize // линиейный - (sum % memSize + offset) % memSize
	}
};

int main() {
	CloseHashTable ht;

	ht.add("str0", 10);
	ht.add("str1", 5);
	ht.add("str2", 7);
	ht.add("str3", 9);
	ht.add("str4", 29);
	ht.add("str5", 3);

	ht.del("str0");

	std::cout << " -- find: str0 -> " << ht.find("str0") << std::endl;
	std::cout << " -- find: str1 -> " << ht.find("str1") << std::endl;
	std::cout << " -- find: str4 -> " << ht.find("str4") << std::endl;

	return 0;
}
