
#include "Chat.h"
#include "SHA1.h"

Chat::Chat() { users = new HashTable(); }

void Chat::reg(const std::string& login, const std::string& pass) {
	users->add(login, sha1(pass));
}

bool Chat::login(const std::string& login, const std::string& pass) const {
	auto userPass = users->find(login);
	if (!userPass) return false;

	auto hash = sha1(pass);
	bool flag = !memcmp(userPass, hash, SHA1HASHLENGTHBYTES);

	delete hash;
	return flag;
}

void Chat::del(const std::string& login) { users->del(login); }

Chat::~Chat() { delete users; }
