
#include "Chat.h"

Chat::Chat(const int& id, const int& from, const std::string& text) : id(id) {
	addMessage(from, text);
}

Chat::Chat(const int& id, const int& from, const int& to, const std::string& text) : id(id) {
	addMessage(from, to, text);
}

void Chat::addMessage(const int& from, const std::string& text) {
	messages.push_back(new Message(from, text));
}

void Chat::addMessage(const int& from, const int& to, const std::string& text) {
	messages.push_back(new Message(from, to, text));
}

auto Chat::getMessages() const -> const std::vector<Message*>& {
	return messages;
}

auto Chat::getLastMessage() const -> Message* {
	int size = messages.size();
	return size ? messages[size - 1] : nullptr;
}
	
auto Chat::getID() const -> const int {
	return id;
}

auto Chat::getUserID(const int& userID) const -> const int {
	auto message = getLastMessage();
	auto userIDto = message->getUserIDto();

	return userID != userIDto ? userIDto : message->getUserIDfrom();
}

auto Chat::isPart(const int& userID) const -> const bool {
	if (id == 0) return true;
	auto message = getLastMessage();
	return userID == message->getUserIDto() || userID == message->getUserIDfrom();
}

Chat::~Chat() {
	for(auto* message : messages) delete message;
}