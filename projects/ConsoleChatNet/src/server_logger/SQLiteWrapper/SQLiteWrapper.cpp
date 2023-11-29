
#include <iostream>

#include "SQLiteWrapper.h"

auto SQLiteWrapper::SQLite::instanse = std::unique_ptr<SQLiteWrapper::SQLite>(nullptr);

SQLiteWrapper::SQLite::SQLite(const std::string& dbFile)
{
	sqlite3_open(dbFile.c_str(), &db);

	// if (sqlite3_open(dbFile.c_str(), &db))
	// 	std::cout << "Error: Cant Open DB! : " << sqlite3_errmsg(db) << std::endl;
	// else
	// 	std::cout << "Open DB Complete..." << std::endl;
}

SQLiteWrapper::SQLite::~SQLite()
{
	auto inst = instanse.get();
	if (inst && inst->db)
	{
		sqlite3_close(inst->db);
		// if (sqlite3_close(inst->db))
		// 	std::cout << "Error: Cant Close DB! : " << sqlite3_errmsg(db) << std::endl;
		// else
		// 	std::cout << "Close DB Complete..." << std::endl;
	} 
}

auto SQLiteWrapper::SQLite::get() -> sqlite3*
{
	return db;
}

auto SQLiteWrapper::SQLite::get_error() -> std::string_view
{
	return sqlite3_errmsg(db);
}

auto SQLiteWrapper::SQLite::init() -> SQLite*
{
	if (!instanse.get()) std::cout << "Error: First init DB need filePath!" << std::endl;
	return instanse.get();
}

auto SQLiteWrapper::SQLite::init(const std::string& dbFile) -> SQLite*
{
	if (!instanse.get()) instanse = std::make_unique<SQLite>(dbFile);
	return instanse.get();
}

auto SQLiteWrapper::SQLite::execute(const std::string& sql) -> QueryDataPtr
{
	sqlite3_stmt* stmt = nullptr;
	// std::cout << "query: " << sql << std::endl;

	auto qd = std::make_unique<QueryData>();
	qd->db = instanse.get();
	auto result = &qd.get()->result;

	if (sql[0] == 'S' || sql[0] == 's')
	{
		if (sqlite3_prepare(db, sql.c_str(), -1, &stmt, NULL))
		{
			std::cout << "Error: SQL : " << sql << std::endl << sqlite3_errmsg(db) << std::endl;
			sqlite3_finalize(stmt);
			return qd;
		}

		auto colunmCount = sqlite3_column_count(stmt);
		while (sqlite3_step(stmt) == SQLITE_ROW)
			for (int i = 0; i < colunmCount; ++i)
				switch (sqlite3_column_type(stmt, i))
				{
					case SQLITE_INTEGER:
						result->push_back(sqlite3_column_int(stmt, i));
						break;

					case SQLITE_FLOAT:
						result->push_back(sqlite3_column_double(stmt, i));
						break;

					case SQLITE_TEXT:
						result->push_back(std::string((char*)sqlite3_column_text(stmt, i)));
						break;
				}

		sqlite3_finalize(stmt);
	}
	else
	{
		if (sqlite3_exec(db, sql.c_str(), NULL, 0, NULL) == SQLITE_OK)
		{
			result->push_back(true);
		}
	}

	return qd;
}
