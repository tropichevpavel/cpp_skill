#pragma once

#include <vector>
#include <string>

#include "entities/User.h"
#include "entities/Chat.h"

constexpr char* usersFile = "users.txt";
constexpr char* mgsFile = "messages.txt";

class App {
	std::vector<User*> users;

	User* user = nullptr;
	std::vector<Chat*> chats;

public:
	App() = default;
	void start();

	void initUsers(const std::vector<User*>& users);
	void initChats(const std::vector<Chat*>& chats);

	auto getUsers() const -> const std::vector<User*>&;
	void addUser(const std::string& login, const std::string& pass, const std::string& name);
	void addUser(const int& id, const std::string& login, const std::string& pass, const std::string& name);
	bool checkUserLogin(const std::string& login) const;
	bool auth(const std::string& login, const std::string& pass);
	void logout();
	bool isLogin() const;

	auto getUser() const -> const User*;
	auto getUserName(const int& id) const -> std::string;

	auto addChat(const int& userIDto, const std::string& text) -> int;
	auto addChat(const int& userIDfrom, const int& userIDto, const std::string& text) -> int;
	auto getChats() const -> const std::vector<Chat*>&;
	auto getChats(const int& userID) const -> const std::vector<Chat*>;
	auto getChat(const int& id) const -> Chat*;

	void addMessage(const int& id, const int& userIDto, const std::string& text);
	void addMessage(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text);

	void loadState();
	void loadStateUsers();
	void loadStateMassages();

	void saveState();
	template<typename T>
	void saveState(const std::string& file, const std::vector<T*>& items);

	~App();
};
