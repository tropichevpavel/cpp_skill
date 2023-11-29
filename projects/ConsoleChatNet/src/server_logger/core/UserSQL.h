#pragma once

#include <string>

#include "../SQLiteWrapper/SQLiteWrapper.h"

namespace dbW
{
	class User final : virtual public SQLiteWrapper::IQueryObject
	{
		uint16_t id = 0;
		std::string login, pass, name;
	public:
		User(const std::string& login, const std::string& pass, const std::string& name) : login(login), pass(pass), name(name) { table = "users"; tablePK = "id"; }
		User(const uint16_t& id, const std::string& login, const std::string& pass, const std::string& name) : id(id), login(login), pass(pass), name(name) { table = "users"; tablePK = "id"; }
		~User() = default;

		auto get_id() -> uint16_t { return id; }
		auto get_name() -> const std::string& { return name; }
		auto upd() -> std::string override;
		auto del() -> std::string override;
		auto ins() -> std::string override;

		void set_name(const std::string& name);
	};
}