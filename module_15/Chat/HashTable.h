#pragma once

#include <iostream>
#include <string>

typedef std::string Key;
typedef unsigned int Val;

class HashTable {
	enum PairStatus {
		free,
		engaged,
		deleted
	};

	struct Pair {
		Key key = "";
		Val* value = nullptr;
		PairStatus status = PairStatus::free;

		Pair() = default;
		Pair(const Key& key, Val* value) : key(key), value(value), status(PairStatus::engaged) {}

		auto operator = (Pair* other) -> Pair&;

		~Pair();
	};

	int memSize = 8;
	int count = 0;
	Pair* data;

public:
	HashTable();

	void add(const Key& key, Val* value);
	void del(const Key& key);

	auto find(const Key& key) const -> Val*;

	void resize();

	~HashTable();

private:
	auto hash(const Key& key, const int& offset = 0) const -> int;
};
