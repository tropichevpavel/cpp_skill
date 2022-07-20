
#include <memory>

#include "App.h"
#include "UI/UI.h"

void App::start() {
	auto ptrUI = std::make_unique<UI>(this);
	ptrUI->start();
}

auto App::getUsers() const -> const std::vector<User*>& {
	return users;
}

void App::addUser(const std::string& login, const std::string& pass, const std::string& name) {
	users.push_back(new User(users.size() + 1, login, pass, name));
}

bool App::checkUserLogin(const std::string& login) const {
	for (const auto& user : users)
		if (user->getLogin() == login) return true;

	return false;
}

bool App::isLogin() const {
	return user;
}

bool App::auth(const std::string& login, const std::string& pass) {
	for (const auto& user : users)
		if (user->auth(login, pass)) {
			this->user = user;
			return true;
		}

	return false;
}

void App::logout() {
	user = nullptr;
}

auto App::getUser() const -> const User* {
	return user;
}

auto App::getUserName(const int& id) const -> std::string {
	if (users.size() >= id)
		return users[id - 1]->getName();
	return "";
}

auto App::getChats() const -> const std::vector<Chat*>& {
	return chats;
}

auto App::getChats(const int& userID) const -> const std::vector<Chat*> {
	std::vector<Chat*> chats = {};

	for (const auto& chat : this->chats)
		if (chat->isPart(userID))
			chats.push_back(chat);

	return chats;
}

auto App::getChat(const int& id) const -> const Chat* {
	return chats[id];
}

auto App::addChat(const int& userIDto, const std::string& text) -> int {
	int size = chats.size();
	chats.push_back(new Chat(size, user->getID(), userIDto, text));
	return size;
}

void App::addMessage(const int& id, const int& userIDto, const std::string& text) {
	chats[id]->addMessage(user->getID(), userIDto, text);
}

App::~App() {
	for (auto& user : users) delete user;
	for (auto& chat : chats) delete chat;
}

void App::initUsers(const std::vector<User*>& users) {
	this->users = users;
}

void App::initChats(const std::vector<Chat*>& chats) {
	this->chats = chats;
}
