#pragma once

#include <string>
#include <fstream>

class User {
	int id = 0;
	std::string login, pass, name;

public:
	User() = default;
	User(const int& id, const std::string& login, const std::string& pass, const std::string& name);

	auto auth(const std::string& login, const std::string& pass) const -> bool;
	auto getID() const -> const int&;
	auto getLogin() const -> const std::string&;
	auto getName() const -> const std::string&;

	friend auto operator << (std::ofstream& is, const User* user) -> std::ofstream&;
};
