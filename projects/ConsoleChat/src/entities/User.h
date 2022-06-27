#pragma once

#include <string>

class User {
	int id;
	std::string login, pass, name;

public:
	User(const int& id, const std::string& login, const std::string& pass, const std::string& name);

	auto auth(const std::string& login, const std::string& pass) const -> const bool;
	auto getID() const -> const int&;
	auto getLogin() const -> const std::string&;
	auto getName() const -> const std::string&;
};
