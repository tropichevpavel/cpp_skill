#pragma once

#include <vector>
#include <fstream>

#include "Message.h"

class Chat {
	unsigned int id;
	std::vector<Message*> messages;

public:
	Chat(const int& id, const int& from, const std::string& text);
	Chat(const int& id, const int& from, const int& to, const std::string& text);

	void addMessage(const int& from, const std::string& text);
	void addMessage(const int& from, const int& to, const std::string& text);

	auto getMessages() const -> const std::vector<Message*>&;
	auto getLastMessage() const -> Message*;
	
	auto getID() const -> int;

	auto getUserID(const int& userID) const -> int;

	auto isPart(const int& userID) const -> bool;

	friend auto operator << (std::ofstream& is, const Chat* user) -> std::ofstream&;

	~Chat();
};
