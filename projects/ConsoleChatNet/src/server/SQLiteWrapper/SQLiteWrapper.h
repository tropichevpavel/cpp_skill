#pragma once

#include <vector>
#include <string>
#include <cstdint>
#include <cmath>

#include "sqlite3.h"

namespace TupleRunner
{
	template <typename T>
	struct RunnerBase : RunnerBase<decltype(&T::operator())> {};

	template <typename R, typename... Args>
	struct RunnerBase<void (R::*)(Args...) const>
	{
		static constexpr std::size_t				size = sizeof...(Args);
		typedef std::tuple<std::decay_t<Args>...>	ArgsTuple;
	};

	template <typename StreamArgsGetter, typename Stream, typename Runner, std::size_t... S>
	void getArgsAndRun(Stream& stream, Runner run, std::index_sequence<S...>)
	{
		run(StreamArgsGetter::template getNext<std::tuple_element_t<S, typename RunnerBase<Runner>::ArgsTuple>>(stream)...);
	}

	template <typename StreamArgsGetter, typename Stream, typename Runner>
	void run(Stream& stream, Runner runner)
	{
		getArgsAndRun<StreamArgsGetter>(stream, runner, std::make_index_sequence<RunnerBase<Runner>::size>());
	}
};

namespace SQLiteWrapper
{
	typedef std::vector<std::variant<bool, int, double, std::string>> DataSet;

	struct IQueryObject
	{
		std::string table, tablePK;

		virtual auto ins() -> std::string = 0;
		virtual auto upd() -> std::string = 0;
		virtual auto del() -> std::string = 0;

		auto val2Str(const std::string& val, const bool& isField = false) { return isField ? val : "'" + val + "'"; }
		auto val2Str(const char * val, const bool& isField = false) { return val2Str(std::string(val), isField); }
		
		template <typename T>
		auto val2Str(const T& val, const bool& = false) { return std::to_string(val); }

		template <typename T>
		auto val2SQL(const T& elem, const bool& isLast = true, const bool& isField = false) -> std::string { return val2Str(elem, isField) + (isLast ? "" : ", "); }

		auto insSQLGeneratorFV(const int32_t&) -> std::string { return ""; }

		template <typename T, typename... Args>
		auto insSQLGeneratorFV(const int32_t& half, const T& elem, Args... other) -> std::string
		{
			if (half > 0)
			{
				return half <= (int32_t)sizeof...(Args) ? val2SQL(elem, half == (int32_t)sizeof...(Args), true) + insSQLGeneratorFV(half, other...) : "";
			}
			else
			{
				return (std::abs(half) <= (int)sizeof...(Args) ? "" : val2SQL(elem, !sizeof...(Args))) + insSQLGeneratorFV(half, other...);
			}
		}

		template <typename... Args>
		auto insSQLGenerator(const std::string& table, Args... other) -> std::string
		{
			auto half = sizeof...(Args) / 2;
			return "INSERT INTO " + table + " (" + insSQLGeneratorFV(half, other...) + ") VALUES (" + insSQLGeneratorFV(-half, other...) + ");";
		}

		auto updSQLGeneratorKV() -> std::string { return ""; }

		template <typename T, typename... Args>
		auto updSQLGeneratorKV(const std::string& key, const T& val, Args... other) -> std::string
		{
			return sizeof...(Args) ? key + " = " + val2SQL(val, sizeof...(Args) == 2) + updSQLGeneratorKV(other...) : " WHERE " + key + " = " + val2SQL(val) + " LIMIT 1;";
		}

		template <typename... Args>
		auto updSQLGenerator(const std::string& table, Args... other) -> std::string
		{
			return "UPDATE " + table + " SET " + updSQLGeneratorKV(other...);
		}

		auto delSQLGenerator(const std::string& table, const std::string& tablePK, const uint32_t& id) -> std::string
		{
			return "DELETE FROM " + table + " WHERE " + tablePK + " = " + val2Str(id) + " LIMIT 1;";
		}

		virtual ~IQueryObject() = default;
	};

	class SQLite
	{
		struct QueryData
		{
			size_t cursor = 0;
			DataSet result;
			SQLite* db;

			auto hasError() -> bool { return !result.size(); }

			template <typename T>
			static T getNext(QueryData& data);

			template <typename T>
			friend void operator >> (std::unique_ptr<QueryData> data, const T& rowHandler)
			{
				data->cursor = 0;
				size_t handlCount = data->result.size() / TupleRunner::RunnerBase<T>::size;
				for (size_t i = 0; i < handlCount; ++i) TupleRunner::run<QueryData>(*data.get(), rowHandler);
			}

			friend auto operator << (std::unique_ptr<QueryData> qd, const std::string& sql) -> std::unique_ptr<QueryData>
			{
				return qd->db ? qd->db->execute(sql) : nullptr;
			}
		};

		typedef std::unique_ptr<QueryData> QueryDataPtr;

		static std::unique_ptr<SQLite> instanse;
		sqlite3* db = nullptr;

	public:
		SQLite(const std::string& dbFile);
		~SQLite();

		auto get() -> sqlite3*;

		static auto init() -> SQLite*;
		static auto init(const std::string& dbFile) -> SQLite*;

		auto execute(const std::string& sql) -> QueryDataPtr;

		friend auto operator << (SQLite& db, const std::string& sql) -> QueryDataPtr
		{
			return db.execute(sql);
		}
	};
}

template <typename T>
T SQLiteWrapper::SQLite::QueryData::getNext(SQLiteWrapper::SQLite::QueryData& data)
{
	T value = {};
	const auto* tPtr = std::get_if<T>(&data.result[data.cursor++]);
	if (tPtr) value = *tPtr;

	return value;
}
