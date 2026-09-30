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

	bool create_tables(sqlite3 *db, std::string sql)
	{

		char *err_msg = nullptr;
		int return_code = sqlite3_exec
		(
			db,
			sql.c_str(),
			nullptr,
			nullptr,
			&err_msg
		);

		if ( DB::SQLite::result_ok_basic("sqlite3_exec", return_code, err_msg) )
			{ return true; }

		return false;

	}

}

namespace DB
{

	std::filesystem::path setup_file(bool delete_file)
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

	bool start_connection(sqlite3 *db, const std::filesystem::path db_file, int return_code)
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
				return true;
			}

		else { std::cout << std::format
				(
					"Connection to {} successful\n",
					db_file.string()
				); }

		return false;

	}

	void close_connection(sqlite3 *db, const std::filesystem::path db_file)
	{

		std::cout << "Closing connection to " << db_file.string() << "...\n";

		sqlite3_close(db);

		std::cout << "Connection terminated.\n";

	}

	namespace Users
	{

		bool insert(sqlite3 *db,
			const std::string& username,
			const std::string& displayName,
			const std::string& email,
			const std::string& role)
		{

			sqlite3_stmt* stmt = nullptr;
			int return_code = sqlite3_prepare_v2(
				db,
				SQL::Insert::users,
				-1,
				&stmt,
				nullptr
			);

			if ( DB::SQLite::result_ok(db, "sqlite3_prepare_v2", return_code) )
				{ return 1; }

			sqlite3_bind_text(stmt, 1, username.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 2, displayName.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 3, email.c_str(), -1, SQLITE_STATIC);
			sqlite3_bind_text(stmt, 4, role.c_str(), -1, SQLITE_STATIC);

			return_code = sqlite3_step(stmt);
			if ( DB::SQLite::result_done(db, "sqlite3_step", return_code) )
				{ return 1; }

				sqlite3_finalize(stmt);

			return 0;

		}

	}

	namespace SQLite
	{

		bool result_ok_basic(std::string descriptor, int return_code, char *err_msg)
		{
			if ( return_code != SQLITE_OK )
				{
					std::cerr << std::format
					(
						"ERR_[{}]: {}\n",
						descriptor,
						err_msg
					);

					sqlite3_free(err_msg);

					return true;
				}

			return false;
		}

		bool result_ok(sqlite3 *db, std::string descriptor, int return_code)
		{
			if ( return_code != SQLITE_OK )
				{
					std::cerr << std::format
					(
						"ERR_[{}]: {}\n",
						descriptor,
						std::string(sqlite3_errmsg(db))
					);

					return true;
				}

			return false;
		}

		bool result_done(sqlite3 *db, std::string descriptor, int return_code)
		{
			if ( return_code != SQLITE_DONE )
				{
					std::cerr << std::format
					(
						"ERR_[{}]: {}\n",
						descriptor,
						std::string(sqlite3_errmsg(db))
					);

					return true;
				}

			return false;
		}

	}

}

