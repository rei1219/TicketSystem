//
// Include libraries
//

#include <iostream>
#include <chrono>
#include <thread>
#include <filesystem>
#include <sqlite3.h>
#include <string>
#include <vector>
#include <format>

//
// Include project headers
//



//
// Macros and Declarations
//

std::filesystem::path db_setup(bool delete_file = true);

bool db_check(sqlite3 *db, const std::filesystem::path db_file, int return_code);


bool SQL_table_create(sqlite3 *db, std::string sql);
bool SQL_table_insert(sqlite3 *db, std::string sql);
bool SQL_table_select(sqlite3 *db, std::string sql);
bool SQL_table_update(sqlite3 *db, std::string sql);
bool SQL_table_delete(sqlite3 *db, std::string sql);


//
// Main Function
//

int main()
{

    std::filesystem::path db_file = db_setup();

    sqlite3 *db = nullptr;
    int return_code = sqlite3_open(db_file.string().c_str(), &db);
    if ( db_check(db, db_file, return_code) == 1 )
    { return 1; }

    while (true)
    {
        std::cout << "Test for systemd.service is running" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(5));
    }

    sqlite3_close(db);

}

//
// Function Definitions
//

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