/**
 * SQLiteHandle.cpp
 *
 * Module: database 
 *
 * Implements SQLiteHandle, SQLiteQuery and SQLiteValue classes.
 *
 */

#include "SQLiteHandle.h"

#include <iostream>
#include <stdexcept>


namespace database {



SQLiteHandle::SQLiteHandle(std::string dbName) {
    int rc = sqlite3_open(dbName.c_str(), &_handle);
    if (rc != SQLITE_OK || _handle == nullptr) {
        std::string errorMsg = getErrorMessage();
        sqlite3_close(_handle);

        throw std::runtime_error(errorMsg);
    }
}



SQLiteHandle::~SQLiteHandle() {
    sqlite3_close(_handle); // TODO
}



std::string SQLiteHandle::getErrorMessage() {
    std::string errMsg {sqlite3_errmsg(_handle)};
    return errMsg;
}



std::string SQLiteHandle::getErrorMessage(int errorCode) {
    std::string errMsg {sqlite3_errstr(errorCode)};
    return errMsg;
}



// --------- SQLiteQuery CLASS ---------

SQLiteQuery::SQLiteQuery(SQLiteHandle& sqlHandle, std::string statement)
    : _sqlHandle{sqlHandle},
      _statement{statement}
{
    // Prepare given statement
    int rc = sqlite3_prepare_v2(_sqlHandle.get(), 
                                _statement.c_str(),
                                _statement.size(),
                                &_ppStmt,
                                nullptr);

    if (rc != SQLITE_OK || _ppStmt == nullptr)
        throw std::runtime_error(_sqlHandle.getErrorMessage());
}



SQLiteQuery::~SQLiteQuery() {
    // Delete resources allocated 
    sqlite3_finalize(_ppStmt);
}



bool SQLiteQuery::exec() {
    int rc = sqlite3_step(_ppStmt);

    if (rc == SQLITE_ROW) {
        _availableRow = true;
        return true;
    } else if (rc == SQLITE_DONE) {
        return true;
    } else 
        return false;
}



bool SQLiteQuery::next() {
    int rc = sqlite3_step(_ppStmt);
    return _availableRow = (rc == SQLITE_ROW);
}



SQLiteValue SQLiteQuery::value(int iCol) {
    int type = sqlite3_column_type(_ppStmt, iCol);
    
    switch(type) {
        case SQLITE_INTEGER:
            return SQLiteValue{sqlite3_column_int(_ppStmt, iCol)};
            break;
        case SQLITE3_TEXT:
            return SQLiteValue{sqlite3_column_text(_ppStmt, iCol)};
            break;
        case SQLITE_FLOAT: // TODO
        case SQLITE_BLOB:  // TODO
        case SQLITE_NULL:  // TODO
        default:
            return SQLiteValue{};
    }
}



bool SQLiteQuery::bindValue(int i, int val) {
    int rc = sqlite3_bind_int(_ppStmt, i, val);
    return rc == SQLITE_OK;
}



bool SQLiteQuery::bindValue(int i, std::string val) {
    int rc = sqlite3_bind_text(_ppStmt, 
                               i, 
                               val.c_str(), 
                               val.size() * sizeof(char), 
                               nullptr);
    return rc == SQLITE_OK;
}



bool SQLiteQuery::bindNull(int i) {
    int rc = sqlite3_bind_null(_ppStmt, i);
    return rc == SQLITE_OK;
}

// --------- SQLiteValue CLASS ---------

SQLiteValue::SQLiteValue()
{
}



SQLiteValue::SQLiteValue(int intVal)
    : _intVal{intVal}
{
}



SQLiteValue::SQLiteValue(const unsigned char *textVal)
    : _textVal{textVal}
{
}



std::string SQLiteValue::toString() {
    return (!_textVal) ? "" : std::string { reinterpret_cast<const char*>(_textVal) };
}



}  // namespace database
