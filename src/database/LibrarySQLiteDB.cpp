/**
 * LibraryDB.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB databse creation, destruction and 
 * configuration.
 *
 */

#include "LibrarySQLiteDB.h"

#include <stdexcept>


namespace database {



LibrarySQLiteDB::LibrarySQLiteDB(std::string dbname) 
    : _dbname {dbname}   
{
    int rc;
    // Open database connection
    rc = sqlite3_open(_dbname.c_str(), &_pDB);
    if (rc != SQLITE_OK || _pDB == nullptr) {
        // Get error message and close database connection
        std::string err_msg{ sqlite3_errmsg(_pDB) };
        sqlite3_close(_pDB);

        // Throw exception
        throw std::runtime_error {err_msg};
    }
}



LibrarySQLiteDB::~LibrarySQLiteDB() 
{
    sqlite3_close(_pDB);
}



}  // namespace database
