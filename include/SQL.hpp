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

	namespace Create
    {

		inline static constexpr const char* tables = R"SQL(

			CREATE TABLE IF NOT EXISTS users(
			id INTEGER PRIMARY KEY, 

			username TEXT NOT NULL UNIQUE, 
			display_name TEXT NOT NULL, 
			email TEXT NOT NULL UNIQUE, 

			role TEXT NOT NULL DEFAULT 'user'
			);


			CREATE TABLE IF NOT EXISTS tickets (
			id INTEGER PRIMARY KEY AUTOINCREMENT, 
			user_id INTEGER NOT NULL, 

			reason TEXT NOT NULL, 

			requested_duration INTEGER NOT NULL, 

			status TEXT NOT NULL DEFAULT 'pending', 

			created_at TEXT NOT NULL, 
			approved_at TEXT, 
			expires_at TEXT, 

			approved_by INTEGER, 

			FOREIGN KEY (user_id) REFERENCES users(id), 
			FOREIGN KEY (approved_by) REFERENCES users(id) 
			);


			CREATE TABLE IF NOT EXISTS ticket_log (
			id INTEGER PRIMARY KEY, 
			request_id INTEGER NOT NULL, 

			event TEXT NOT NULL, 
			timestamp TEXT NOT NULL, 

			ip_address TEXT, 
			device_name TEXT, 

			performed_by INTEGER, 

			FOREIGN KEY (request_id) REFERENCES requests(id), 
			FOREIGN KEY (performed_by) REFERENCES users(id)
			);

		)SQL";
		
	}

	namespace Insert
	{

		inline static constexpr const char* users = R"SQL(

			INSERT INTO users
			(username, display_name, email, role)
			VALUES 
			(?, ?, ?, ?);

		)SQL";

		inline static constexpr const char* tickets = R"SQL(

			INSERT INTO tickets
			(user_id, reason, requested_duration, created_at)
			VALUES 
			(?, ?, ?, ?, ?, ?, ?, ?);

		)SQL";

		inline static constexpr const char* ticket_log = R"SQL(

			INSERT INTO ticket_log
			(request_id, event, timestamp, ip_address, device_name, performed_by)
			VALUES 
			(?, ?, ?, ?);

		)SQL";

	}

    inline static constexpr const char* tableSelect =
		"SELECT *"
		"FROM Characters;";

	inline static constexpr const char* tableUpdate =
		"UPDATE Characters "
		"SET name = ?, software = ? "
		"WHERE id = ?;";

	inline static constexpr const char* tableDelete =
		"DELETE FROM Characters "
		"WHERE id = ?;";

	bool create_tables(sqlite3 *db, std::string sql);

}

namespace DB
{

	std::filesystem::path setup_file(bool delete_file = true);

	bool start_connection(sqlite3 *db, const std::filesystem::path db_file, int return_code);
	void close_connection(sqlite3 *db, const std::filesystem::path db_file);
	
	namespace Users
	{

			bool insert(sqlite3 *db,
			const std::string& username,
			const std::string& displayName,
			const std::string& email,
			const std::string& role);

	}

	namespace SQLite
	{

		bool result_ok_basic(std::string descriptor, int return_code, char *err_msg);
		bool result_ok(sqlite3 *db, std::string descriptor, int return_code);
		bool result_done(sqlite3 *db, std::string descriptor, int return_code);

	}

}



#endif