#pragma once

#include <iostream>
#include <string>

class Human {
	int id;
	std::string name;

public:
	Human(const int& id, const std::string& name);

	auto getID() const -> const int&;
	auto getName() const -> const std::string&;

	friend auto operator<< (std::ostream& out, const Human* h) -> std::ostream&;
};
