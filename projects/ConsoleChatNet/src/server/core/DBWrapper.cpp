#include "DBWrapper.h"

#include <iostream>
#include <string>

#include "../SQLiteWrapper/SQLiteWrapper.h"

bool dbW::init()
{
	db = SQLiteWrapper::SQLite::init("./db.sqlite");

	if (!db) return false;

	*db << "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, login TEXT NOT NULL UNIQUE, pass TEXT NOT NULL, name TEXT NOT NULL);"
		<< "CREATE TABLE IF NOT EXISTS messages (chat_id INTEGER NOT NULL, user_id INTEGER NOT NULL, user_id_to INTEGER NOT NULL, text TEXT NOT NULL);";

	return true;
}

auto dbW::auth(const std::string& login, const std::string& pass, dbW::User*& user) -> bool
{
	*db << "SELECT id, name FROM users WHERE login = '" + login + "' AND pass = '" + pass + "';"
		>> [&] (const int& id, const std::string& name) { user = new User(id, login, pass, name); };
	return user;
}

auto dbW::add_user(const std::string& login, const std::string& pass, const std::string& name) -> bool
{
	User u(login, pass, name);
	return !(*db << u.ins())->hasError();
}

auto dbW::get_msgs(const unsigned int& user_id) -> std::string
{
	std::string list = "";
	*db << "SELECT chat_id id, user_id uid, user_id_to uidt, text FROM messages WHERE uidt = -1 OR uid = " + std::to_string(user_id) + " OR uidt = " + std::to_string(user_id) +";"
		>> [&list] (const int& id, const int& uid, const int& uidt, const std::string& text)
		{
			list += std::to_string(id) + " " + std::to_string(uid) + " " + std::to_string(uidt) + " " + text + "\n";
		};
	return list;
}

bool dbW::add_msg(const unsigned int& user_id, const int& chat_id, const int& user_id_to, const std::string& text)
{ 
	if (chat_id < 0)
	{
		if (user_id_to == -1)
		{
			return !(*db << "INSERT INTO messages VALUES (0, " + std::to_string(user_id) + ", " + std::to_string(user_id_to) + ", " + "'" + text + "'" + ");")->hasError();	
		}

		return !(*db << "INSERT INTO messages VALUES ((SELECT IIF(last_id IS NULL, 1, last_id + 1) last_id FROM (SELECT MAX(chat_id) last_id FROM messages)), " + std::to_string(user_id) + ", " + std::to_string(user_id_to) + ", " + "'" + text + "'" + ");")->hasError();	
	}

	return !(*db << "INSERT INTO messages VALUES (" + std::to_string(chat_id) + ", " + std::to_string(user_id) + ", " + std::to_string(user_id_to) + ", " + "'" + text + "'" + ");")->hasError();
}

auto dbW::get_chat_id_last(const unsigned int& user_id) -> int
{
	int chat_id_last = -1;
	*db << "SELECT IIF(last_id IS NULL, -1, last_id) last_id FROM (SELECT MAX(chat_id) last_id FROM messages WHERE user_id = " + std::to_string(user_id) + ");" >> [&chat_id_last](const int& last_id)
	{
		chat_id_last = last_id;
	};
	return chat_id_last;
}

auto dbW::get_users() -> std::string
{
	std::string list = "";
	*db << "SELECT id, login, name FROM users;" >> [&list] (const int& id, const std::string& login, const std::string& name) { list += std::to_string(id) + " " + login + " " + name + "\n"; };
	return list;
}
