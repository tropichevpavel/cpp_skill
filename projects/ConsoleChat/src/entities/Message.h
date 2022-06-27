#pragma once

#include <string>

class Message {
	unsigned int userIDfrom;
	int userIDto = -1;
	std::string text;

public:
	Message(const unsigned int& from, const std::string& text);
	Message(const unsigned int& from, const unsigned int& to, const std::string& text);

	auto getText() const -> const std::string&;
	auto getUserIDfrom() const -> const int;
	auto getUserIDto() const -> const int;
};
