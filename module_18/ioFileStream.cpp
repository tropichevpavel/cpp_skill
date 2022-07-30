
#include <iostream>
#include <fstream>
#include <string>

class User {
	std::string name;
	std::string login;
	std::string pass;

public:
	User(const std::string& name, const std::string& login, const std::string& pass) : name(name), login(login), pass(pass) {}

	friend std::fstream& operator >> (std::fstream& is, User& user);
	friend std::ostream& operator << (std::ostream& os, const User& user);
};

auto operator >>(std::fstream& is, User& user) -> std::fstream& {
	is >> user.name >> user.login >> user.pass;
	return is;
}

auto operator << (std::ostream& os, const User& user) -> std::ostream& {
	os << user.name << ' ' << user.login << ' ' << user.pass;
	return os;
}

int main() {
	std::fstream fs = std::fstream("user.txt", std::ios::in | std::ios::out);
	if (!fs) fs = std::fstream("user.txt", std::ios::in | std::ios::out | std::ios::trunc);
	
	if (fs) {
		User u1("Test1", "test", "12345");
		fs << u1 << std::endl;

		fs.seekg(0, std::ios::beg);

		fs >> u1;
		std::cout << u1 << std::endl;

	} else
		std::cout << "Cant open/create file!" << std::endl;
	return 0;
}
