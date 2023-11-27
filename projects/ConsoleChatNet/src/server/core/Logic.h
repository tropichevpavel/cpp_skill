#pragma once

#include <string>

namespace Logic
{
	enum
	{
		LOGIN,
		REGISTER,
		GET_USERS,
		GET_MESSAGES,
		SEND,
		GET_CHAT_ID_LAST
	}
	COMMAND;

	auto parse(const std::string& buffer, std::string& answer) -> std::string&;
	void init_db();
};
