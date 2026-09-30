#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <format>

#include "SQL.hpp"

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

std::filesystem::path db_setup(bool delete_file)
{
	const std::filesystem::path db_dir = "db";
	const std::filesystem::path db_file = db_dir / "test.db";

	if (!std::filesystem::exists(db_dir))
	{
		std::filesystem::create_directory(db_dir);
		std::cout << std::format("Created directory: {}/\n", db_dir.string());
	}

	if (std::filesystem::remove(db_file) && ( delete_file == true ))
		{ std::cout << std::format("Removed file: {}\n", db_file.string()); }

	return db_file;
}

bool db_check(sqlite3 *db, const std::filesystem::path db_file, int return_code)
{
	if ( return_code != SQLITE_OK )
		{
			std::cerr << std::format
			(
				"Connection to {} failure: {}\n",
				db_file.string(),
                sqlite3_errmsg(db)
			);

			sqlite3_close(db);
			return 1;
		}

	else { std::cout << std::format
			(
				"Connection to {} successful\n",
				db_file.string()
			); }

	return 0;
}



}