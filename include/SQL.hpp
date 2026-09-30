#ifndef SQL_HPP
#define SQL_HPP

#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <format>

namespace SQL
{
    std::string crt =
        "CREATE TABLE IF NOT EXISTS Characters("
		"id INTEGER PRIMARY KEY AUTOINCREMENT, "
		"name TEXT NOT NULL, "
		"software TEXT NOT NULL);";

    std::string ins =
		"INSERT INTO Characters (name, software)"
		"VALUES (?, ?);";

    std::string sel =
	"SELECT *"
	"FROM Characters;";

	std::string upd =
	"UPDATE Characters "
	"SET name = ?, software = ? "
	"WHERE id = ?;";

	std::string del =
	"DELETE FROM Characters "
	"WHERE id = ?;";
}

namespace Database
{

std::filesystem::path db_setup(bool delete_file = true);

bool db_check(sqlite3 *db, const std::filesystem::path db_file, int return_code);

bool table_create(sqlite3 *db, std::string sql);
bool table_insert(sqlite3 *db, std::string sql);
bool table_select(sqlite3 *db, std::string sql);
bool table_update(sqlite3 *db, std::string sql);
bool table_delete(sqlite3 *db, std::string sql);


}

#endif