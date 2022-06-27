
#include "User.h"

User::User(const int& id, const std::string& login, const std::string& pass, const std::string& name) : id(id), login(login), pass(pass), name(name) {}

auto User::auth(const std::string& login, const std::string& pass) const -> const bool {
	return login == this->login && pass == this->pass;
}

auto User::getID() const -> const int& {
	return id;
}

auto User::getLogin() const -> const std::string&  {
	return login;
}

auto User::getName() const -> const std::string& {
	return name;
}
