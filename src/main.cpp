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

#include "SQL.hpp"

//
// Macros and Declarations
//


//
// Main Function
//

int main()
{
	bool isRunning = 1;
	int loopFor = 3;
	int counter = 0;

    std::filesystem::path db_file = DB::setup_file();

    sqlite3 *db = nullptr;
    int return_code = sqlite3_open(db_file.string().c_str(), &db);
    if ( DB::start_connection(db, db_file, return_code) == true )
    	{ isRunning = 0; }

	if ( SQL::create_tables(db, SQL::Create::tables) == true )
		{ isRunning = 0; }

	if ( DB::Users::insert(db, "lilith", "Lilith", "lilith@hotmail.com", "dev") == true )
		{ isRunning = 0; }

    while (isRunning)
    {

		counter++;

        std::cout << counter <<"-systemd.service is running" << std::endl;

		if ( counter >= loopFor )
			{ isRunning = 0; }

        std::this_thread::sleep_for(std::chrono::seconds(5));

    }

	DB::close_connection(db, db_file);

	return 0;

}

//
// Function Definitions
//
