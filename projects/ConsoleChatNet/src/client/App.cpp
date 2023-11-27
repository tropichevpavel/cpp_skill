
#include <memory>
#include <fstream>
#include <functional>

#include "App.h"
#include "UI/UI.h"

void App::start()
{
	api.init();
	auto ptrUI = std::make_unique<UI>(this);
	ptrUI->start();
}

auto App::getUsers() const -> const std::vector<User*>& {
	return users;
}

void App::addUser(const std::string& login, const std::string& pass, const std::string& name)
{
	api.add_users(login, pass, name);
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

bool App::auth(const std::string& login, const std::string& pass)
{
	return api.auth(login, pass, this->user);
}

void App::logout()
{
	if (user) delete user;
	user = nullptr;
}

auto App::getUser() const -> const User*
{
	return user;
}

auto App::getUserName(const int& id) const -> std::string
{
	for (auto& user : users)
	{
		if (user->getID() == id) return user->getName();
	}
	return "";
}

auto App::getChats() const -> const std::vector<Chat*>&
{
	return chats;
}

auto App::getChats(const int& userID) const -> const std::vector<Chat*>
{
	std::vector<Chat*> chats = {};

	for (const auto& chat : this->chats)
		if (chat->isPart(userID))
			chats.push_back(chat);

	return chats;
}

auto App::getChat(const int& id) const -> Chat*
{
	return chats[id];
}

auto App::getChatByID(const int& id) const -> Chat*
{
	for (auto& chat : chats)
	{
		if (chat->getID() == id) return chat;
	}
	return nullptr;
}

auto App::addChat(const int& userIDto, const std::string& text) -> int
{
	return addChat(user->getID(), userIDto, text);
}

auto App::addChat(const int& userIDfrom, const int& userIDto, const std::string& text) -> int
{
	int size = chats.size();
	chats.push_back(new Chat(size, userIDfrom, userIDto, text));
	return size;
}

void App::addChat(const int& chat_id, const int& user_id, const int& user_id_to, const std::string& text)
{
	chats.push_back(new Chat(chat_id, user_id, user_id_to, text));
}

auto App::addChatServer(const int& user_id_to, const std::string& text) -> int
{
	if (api.add_msg(-1, user->getID(), user_id_to, text)) return api.get_chat_id_last(user->getID());
	return -1;
}

void App::addMessage(const int& id, const int& userIDto, const std::string& text)
{
	addMessage(id, user->getID(), userIDto, text);
}

void App::addMessage(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text)
{
	Chat* chat_ptr = getChatByID(id);
	if (chat_ptr) chat_ptr->addMessage(userIDfrom, userIDto, text);
	else addChat(id, userIDfrom, userIDto, text);
}

void App::addMessageServer(const int& chat_id, const int& user_id, const int& user_id_to, const std::string& text)
{
	api.add_msg(chat_id, user_id, user_id_to, text);
}

bool App::checkUserIDInChats(const int& user_id)
{
	for (auto& chat : chats)
	{
		if (chat->getUserID(user->getID()) == user_id) return true;
	}

	return false;
}

App::~App()
{
	for (auto& user : users) delete user;
	for (auto& chat : chats) delete chat;
}

void App::initUsers(const std::vector<User*>& users)
{
	this->users = users;
}

void App::initChats(const std::vector<Chat*>& chats)
{
	this->chats = chats;
}

void App::loadState()
{
	loadStateUsers();
	loadStateMassages();
}

void App::loadStateUsers()
{
	for (auto& user : users) delete user;
	users.clear();

	if (!([] (std::vector<Chat*>& chats) -> bool { for (auto& chat : chats) if (chat->getID() == 0) return true; return false; })(chats))
	{
		users.push_back(new User(0, "General chat", "", ""));
	}

	api.get_users(user ? user->getID() : 0, &users);
}

void App::loadStateMassages()
{
	std::function<void(const int& id, const int& userIDfrom, const int& userIDto, const std::string& text)> func =
	[&](const int& chat_id, const int& userIDfrom, const int& userIDto, const std::string& text)
	{
		addMessage(chat_id, userIDfrom, userIDto, text);
	};

	for (auto& chat : chats) delete chat;
	chats.clear();

	api.get_msgs(this->user->getID(), func);
}
