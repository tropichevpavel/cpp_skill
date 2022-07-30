
#include <memory>
#include <fstream>

#include "App.h"
#include "UI/UI.h"

void App::start() {
	loadState();
	auto ptrUI = std::make_unique<UI>(this);
	ptrUI->start();
}

auto App::getUsers() const -> const std::vector<User*>& {
	return users;
}

void App::addUser(const std::string& login, const std::string& pass, const std::string& name) {
	addUser(users.size() + 1, login, pass, name);
}

void App::addUser(const int& id, const std::string& login, const std::string& pass, const std::string& name) {
	users.push_back(new User(id, login, pass, name));
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

auto App::getChat(const int& id) const -> Chat* {
	return chats[id];
}

auto App::addChat(const int& userIDto, const std::string& text) -> int {
	int size = chats.size();
	chats.push_back(new Chat(size, user->getID(), userIDto, text));
	return size;
}

auto App::addChat(const int& userIDfrom, const int& userIDto, const std::string& text) -> int {
	int size = chats.size();
	chats.push_back(new Chat(size, userIDfrom, userIDto, text));
	return size;
}

void App::addMessage(const int& id, const int& userIDto, const std::string& text) {
	if (id < chats.size()) chats[id]->addMessage(user->getID(), userIDto, text);
	else addChat(userIDto, text);
}

void App::addMessage(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text) {
	if (id < chats.size()) chats[id]->addMessage(userIDfrom, userIDto, text);
	else addChat(userIDfrom, userIDto, text);
}

App::~App() {
	saveState();
	for (auto& user : users) delete user;
	for (auto& chat : chats) delete chat;
}

void App::initUsers(const std::vector<User*>& users) {
	this->users = users;
}

void App::initChats(const std::vector<Chat*>& chats) {
	this->chats = chats;
}

void App::loadState() {
	loadStateUsers();
	loadStateMassages();
}

void App::loadStateUsers() {
	std::ifstream fs = std::ifstream(usersFile);

	if (fs) {
		// int id;
		// std::string login, pass, name;
		// while (fs >> id >> login >> pass >> name)
		// 	addUser(id, login, pass, name);
		std::string line;

		while (std::getline(fs, line)) {
			try {
				int pos = line.find_first_of(' ');

				addUser(std::stoi(line.substr(0, pos)), // id
						line.substr(++pos, abs(pos - (pos = line.find_first_of(' ', pos)))), // login
						line.substr(++pos, abs(pos - (pos = line.find_first_of(' ', pos)))), // pass
						line.substr(++pos, line.size() - pos)); // name
			} catch (...) {
				std::cout << "Error while load user!";
			}
		}

		fs.close();

	} else
		std::cout << "Cant open " << usersFile << " file!" << std::endl;
}

void App::loadStateMassages() {
	std::ifstream fs = std::ifstream(mgsFile);

	if (fs) {
		std::string line;

		while (std::getline(fs, line)) {
			try {
				int pos = line.find_first_of(' ');

				addMessage(	std::stoi(line.substr(0, pos)), // chatID
							std::stoi(line.substr(++pos, abs(pos - (pos = line.find_first_of(' ', pos))))), // userIDfrom
							std::stoi(line.substr(++pos, abs(pos - (pos = line.find_first_of(' ', pos))))), // userIDto
							line.substr(++pos, line.size() - pos)); // text
			} catch (...) {
				std::cout << "Error while load msg!";
			}
		}

		fs.close();

	} else
		std::cout << "Cant open " << mgsFile << " file!" << std::endl;
}

void App::saveState() {
	saveState(usersFile, users);
	saveState(mgsFile, chats);
}

template<typename T>
void App::saveState(const std::string& file, const std::vector<T*>& items) {
	std::ofstream fs = std::ofstream(file);
	if (!fs) fs = std::ofstream(file, std::ios::trunc);

	if (fs) {
		for (const T* item : items) fs << item << std::endl;

		fs.close();

	} else
		std::cout << "Cant open/create " << file << " file!" << std::endl;
}
