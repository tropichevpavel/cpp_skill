#pragma once

#include <string>

#include "../SQLiteWrapper/SQLiteWrapper.h"
#include "UserSQL.h"
#include "Logger.h"

namespace dbW
{
	static SQLiteWrapper::SQLite* db;

	bool init();

	auto auth(const std::string& login, const std::string& pass, dbW::User*& user) -> bool;
	auto add_user(const std::string& login, const std::string& pass, const std::string& name) -> bool;
	auto get_users() -> std::string;

	auto get_chat_id_last(const unsigned int& user_id) -> int;	
	auto add_chat(const unsigned int& user_id, const unsigned int& user_id_to, const std::string& text) -> int;
	bool add_msg(const unsigned int& user_id, const int& chat_id, const int& user_id_to, const std::string& text);
	auto get_msgs(const unsigned int& user_id) -> std::string;
};
