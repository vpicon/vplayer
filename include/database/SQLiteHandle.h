/**
 * SQLiteHandle.h
 *
 * Module: database 
 *
 * Defines SQLiteHandle, SQLiteQuery and SQLiteValue class interfaces.
 *
 */

#ifndef _VPLAYER_SQLITE_HANDLE_H
#define _VPLAYER_SQLITE_HANDLE_H


#include <sqlite3.h>
#include <string>


namespace database {



class SQLiteValue;
class SQLiteQuery;


/**
 * A class to handle the objects to manipulate the connection to 
 * an sqlite3 database.
 */
class SQLiteHandle {
public:
    SQLiteHandle(std::string dbName);

    ~SQLiteHandle();


    std::string getErrorMessage();

    std::string getErrorMessage(int errorCode);
    
    sqlite3 *get() { return _handle; }

private:
    sqlite3 *_handle;    
};



/**
 * A class handle to query a database handle object.
 */
class SQLiteQuery {
public:
    /**
     * Prepares a new query for the given sql database, with the
     * given statement.
     */
    SQLiteQuery(SQLiteHandle& sqlHandle, std::string statement);

    ~SQLiteQuery();

    /**
     * Executes a previously prepared SQL query. Returns true if the query 
     * executed successfully; otherwise returns false.
     */
    bool exec();

    /**
     * Retrieves the next record in the result, if available, and positions 
     * the query on the retrieved record.
     *
     * Returns if there are still more columns left to be retrieved.
     */
    bool next();  // TODO: implement as iterators

    /**
     * When this query returns a record (row) of the database, returns
     * the SQLiteValue stored at the iCol position of the record.
     */
    SQLiteValue value(int iCol);

    /**
     * Tells if there is an associated record with the current query and state
     * of the query.
     */
    bool availableRow() { return _availableRow; }

    /**
     * Binds values to a prepared statement query. The first parameter is the 
     * position (index) of the SQL argument, starting with 1.
     * Return true on success, false otherwise.
     */
    bool bindValue(int i, int val);
    bool bindValue(int i, std::string val);
    bool bindNull(int i);

    /**
     * Returns the id of the last successful INSERT operation.
     */
    int lastInsertId() { return sqlite3_last_insert_rowid(_sqlHandle.get()); };

private:
    SQLiteHandle& _sqlHandle;
    std::string _statement;

    sqlite3_stmt *_ppStmt = nullptr;  // SQLite3 statement handle

    bool _availableRow = false;
};



/**
 * A class representing the values returned by column operation 
 * in the sqlite3 object.
 */
class SQLiteValue {
public:
    explicit SQLiteValue();
    explicit SQLiteValue(int intVal);
    explicit SQLiteValue(const unsigned char *textVal);

    int toInt() { return _intVal; }
    std::string toString();

private:
    int _intVal;
    const unsigned char *_textVal;
};



}  // namespace database



#endif  // _VPLAYER_SQLITE_HANDLE_H
