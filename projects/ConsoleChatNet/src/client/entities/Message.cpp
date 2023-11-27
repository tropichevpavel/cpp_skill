
#include "Message.h"

Message::Message(const unsigned int& from, const std::string& text) : userIDfrom(from), text(text) {}
Message::Message(const unsigned int& from, const unsigned int& to, const std::string& text) : userIDfrom(from), userIDto(to), text(text) {}

auto Message::getText() const -> const std::string& {
	return this->text;
}

auto Message::getUserIDfrom() const -> int {
	return this->userIDfrom;
}

auto Message::getUserIDto() const -> int {
	return this->userIDto;
}
