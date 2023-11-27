#include <string>

#include "UserSQL.h"

auto dbW::User::ins() -> std::string
{
	return insSQLGenerator(table, "login", "pass", "name", login, pass, name);
}

auto dbW::User::upd() -> std::string
{
	return updSQLGenerator(table, "login", login, "pass", pass, "name", name, tablePK, id);
}

auto dbW::User::del() -> std::string
{
	return delSQLGenerator(table, tablePK, id);
}

void dbW::User::set_name(const std::string& name)
{
	this->name = name;
}
