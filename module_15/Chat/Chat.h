#pragma once

#include <string>

#include "HashTable.h"

class Chat {
	HashTable* users;

public:
	Chat();

	void reg(const std::string& login, const std::string& pass);
	bool login(const std::string& login, const std::string& pass) const;
	void del(const std::string& login);

	~Chat();
};
