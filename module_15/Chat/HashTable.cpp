
#include "HashTable.h"

HashTable::HashTable() { data = new Pair[memSize]; }

void HashTable::add(const Key& key, Val* value) {
	int index = -1, i = 0;
	for (; i < memSize; ++i)
		if (data[index = hash(key, i)].status != PairStatus::engaged)
			break;

	if (i >= memSize) {
		resize();
		add(key, value);
		return;
	}

	data[index] = new Pair(key, value);
	++count;
}

void HashTable::del(const Key& key) {
	int index = 0, i = 0;
	for (; i < memSize; ++i)
		if (data[index = hash(key, i)].status == PairStatus::engaged && data[index].key == key) {
			data[index].status = PairStatus::deleted;
			if (data[index].value) delete data[index].value;

		} else if (data[index].status == PairStatus::free) break;
}

auto HashTable::find(const Key& key) const -> Val* {
	int index = 0, i = 0;
	for (; i < memSize; ++i)
		if (data[index = hash(key, i)].status == PairStatus::engaged && data[index].key == key)
			return data[index].value;
		else if (data[index].status == PairStatus::free) return nullptr;
	return nullptr;
}

void HashTable::resize() {
	Pair* oldData = data;
	int oldMemSizee = memSize;

	memSize *= 2;
	count = 0;

	data = new Pair[memSize];
	for (int i = 0; i < memSize; ++i)
		if (oldData[i].status == PairStatus::engaged) {
			add(oldData[i].key, oldData[i].value);
			oldData[i].value = nullptr;
		}

	delete[] oldData;
}

auto HashTable::hash(const Key& key, const int& offset) const -> int {
	const int M = 20;
	const double A = 0.6;
	int sum = 0;
	for (const auto& ch : key) sum += ch;
	return (int(M * (A * sum - int(A * sum))) % memSize + offset * offset) % memSize;
}

HashTable::~HashTable() { delete[] data; }

auto HashTable::Pair::operator = (Pair* other) -> Pair& {
	key = other->key;
	value = other->value;
	status = other->status;
	other->value = nullptr;
	delete other;
	return *this;
}

HashTable::Pair::~Pair() {
	if (value && status == PairStatus::engaged) { delete value; }
}
