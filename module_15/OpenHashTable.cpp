
#include <iostream>
#include <string>

typedef std::string Key;

class OpenHashTable {
	struct ChainNode {
		Key key;
		int value;

		ChainNode* next = nullptr;

		ChainNode(Key key, int value) : key(key), value(value) {}
		~ChainNode() { if (next) delete next; }
	};

	int memSize = 8;
	int count = 0;
	ChainNode** data;

public:
	OpenHashTable() {
		data = new ChainNode*[memSize];
		for (int i = 0; i < memSize; ++i)
			data[i] = nullptr;
	}

	void add(Key key, int value) {
		if (count / memSize > 3) resize(); // 3 - случайный индекс, нормальный высчитывается по опыту

		int index = hash(key);

		if (data[index]) {
			ChainNode* node = new ChainNode(key, value);
			node->next = data[index];
			data[index] = node;

		} else
			data[index] = new ChainNode(key, value);

		++count;
	}

	int find(Key key) {
		ChainNode* node = data[hash(key)];

		while (node) {
			if (node->key == key) return node->value;
			node = node->next;
		}

		return -1;
	}

	void del(Key key) {
		ChainNode* node = data[hash(key)];

		if (node->key == key) {
			delete node;
			data[hash(key)] = nullptr;
			return;
		}

		ChainNode* parNode = node;

		while (node) {
			if (node->key == key) {
				parNode->next = node->next;
				delete node;
				return;
			}
			parNode = node;
			node = node->next;
		}
	}

	void resize() {
		ChainNode** oldData = data;
		int oldMemSize = memSize;

		memSize *= 2;
		count = 0;
		data = new ChainNode*[memSize];
		for (int i = 0; i < memSize; ++i)
			data[i] = nullptr;

		for (int i = 0; i < oldMemSize; ++i) {
			ChainNode* node = oldData[i];
			while(node) {
				add(node->key, node->value);
				node = node->next;
			}
		}

		for (int i = 0; i < oldMemSize; ++i)
			if (oldData[i]) delete oldData[i];
		
		delete[] oldData;
	}

	~OpenHashTable() {
		for (int i = 0; i < memSize; ++i)
			if (data[i]) delete data[i];
		delete[] data;
	}

private:
	int hash (Key key) {
		int sum = 0;
		for (const auto& ch : key) sum += ch;
		return sum % memSize;
	}
};

int main() {
	OpenHashTable ht;

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
