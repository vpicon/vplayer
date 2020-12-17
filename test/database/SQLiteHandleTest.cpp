/** 
 * SQLiteHandleTest.cpp
 *
 * Module: test/database
 *
 * Unit tests of the SQLiteHandleTest class.
 *
 */

#include "gtest/gtest.h"
#include "SQLiteHandle.h"

#include <string>


namespace {


// HELPER METHODS AND DEFINITIONS
struct Person {
    int id = 0;
    std::string name = "";
    int age = 0;

    Person(int id_, std::string name_, int age_)
        : id{id_}, name{name_}, age{age_} {}

    Person(std::string name_, int age_)
        : Person(0, name_, age_) {}
};



/**
 * Add person to database, and sets its id.
 */
void addPersonToDatabase(Person &person, database::SQLiteHandle &sqlHandle) {
        // Add person to the database
        std::string insertStmt {
            "INSERT INTO Persons ("
                "name,"
                "age"
            ") VALUES ("
                "\'" + person.name + "\',"
                     + std::to_string(person.age) + 
            ");"
        };
        database::SQLiteQuery insertQuery {sqlHandle, insertStmt};
        insertQuery.exec();

        person.id = insertQuery.lastInsertId();  
}


// FIXTURE

class SQLiteHandleTest : public testing::Test {
protected:
    void SetUp() override {
        // Create Persons Table
        std::string createTableStmt {
            "CREATE TABLE IF NOT EXISTS Persons ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "name TEXT NOT NULL,"
                "age INTEGER"
            ");"
        };

        database::SQLiteQuery query{sqlHandle, createTableStmt};
        ASSERT_TRUE(query.exec());

        // Add person to the database
        addPersonToDatabase(p1, sqlHandle);
    }

    void TearDown() override {
        // Delete Persons Table
        std::string statement {
            "DROP TABLE IF EXISTS Persons;"
        };

        database::SQLiteQuery query{sqlHandle, statement};
        ASSERT_TRUE(query.exec());
    }
    
    // Declare database handles
    std::string dbName {"test/.sqliteHandleTest.db"};
    database::SQLiteHandle sqlHandle {dbName};

    // Declare some objects to play with the database
    Person p1 {"Cory Wong", 29};
    Person p2 {"Theo Katzman", 31};
};

// UNIT TESTS

/**
 * SQLiteHandle Class constructor and get handle test
 */

TEST_F(SQLiteHandleTest, SQLiteHandleClassGetHandle) {
    // Check the sqlite3 * pointer handle is not null
    EXPECT_NE(sqlHandle.get(), nullptr);
}



/**
 * SQLiteValue Class getters and constructors.
 */

TEST_F(SQLiteHandleTest, SQLiteValueClassIntVal) {
    // Build SQLiteValue object from integer
    int x = 3;
    database::SQLiteValue intValObj {x};

    // Check the value returned
    EXPECT_EQ(intValObj.toInt(), x);
}

TEST_F(SQLiteHandleTest, SQLiteValueClassTextVal) {
    // Build SQLiteValue object from integer
    const unsigned char x[] = {'a', '\0'};
    database::SQLiteValue textValObj {x};

    // Check the value returned
    EXPECT_EQ(textValObj.toString(), std::string{"a"});
}


/**
 * SQLiteQuery.exec() Test 
 *    return: true, false (TODO)
 */

TEST_F(SQLiteHandleTest, SQLiteQueryClassExecSucess) {
        // Create statement of creating the Persons table again
        std::string createTableStmt {
            "CREATE TABLE IF NOT EXISTS Persons ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "name TEXT NOT NULL,"
                "age INTEGER"
            ")"
        };

        // Build query
        database::SQLiteQuery query{sqlHandle, createTableStmt};

        // Execute the query. Should run successfully, but have no effect
        // on the database.
        EXPECT_TRUE(query.exec());
}



/**
 * SQLiteQuery.availableRecord() Test 
 *    return: true, false
 *    state: false after true, true after false (TODO: from a reset)
 */

TEST_F(SQLiteHandleTest, SQLiteQueryClassavailableRecordFalse) {
        // Create statement of creating the Persons table again
        std::string createTableStmt {
            "CREATE TABLE IF NOT EXISTS Persons ("
                "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
                "name TEXT NOT NULL,"
                "age INTEGER"
            ")"
        };

        // Build query
        database::SQLiteQuery query{sqlHandle, createTableStmt};

        // Execute the query. Should run successfully, but have no effect
        // on the database.
        ASSERT_TRUE(query.exec());

        // Check if we have some available records (we shouldnt)
        EXPECT_FALSE(query.availableRecord());
}

TEST_F(SQLiteHandleTest, SQLiteQueryClassavailableRecordTrue) {
        // Create statement of creating the Persons table again
        std::string statement {
            "SELECT id FROM Persons;"
        };

        // Build query
        database::SQLiteQuery query{sqlHandle, statement};

        // Execute the query. Should run successfully, but have no effect
        // on the database.
        ASSERT_TRUE(query.exec());

        // Check if we have some available records (we shouldnt)
        EXPECT_TRUE(query.availableRecord());
}

TEST_F(SQLiteHandleTest, SQLiteQueryClassavailableRecordFalseAfterTrue) {
        // Create statement of creating the Persons table again
        std::string statement {
            "SELECT id FROM Persons;"
        };

        // Build query
        database::SQLiteQuery query{sqlHandle, statement};

        // Execute the query. Should run successfully, but have no effect
        // on the database.
        ASSERT_TRUE(query.exec());

        // Check if we have some available records (we shouldnt)
        EXPECT_TRUE(query.availableRecord());

        // Go to next result (if any)
        EXPECT_FALSE(query.next());

        // Check available records
        EXPECT_FALSE(query.availableRecord());
}



/**
 * SQLiteQuery.next() Test 
 *    return: true, false
 */

TEST_F(SQLiteHandleTest, SQLiteQueryClassNext) {
        // Add another person to databaseTrue
        addPersonToDatabase(p2, sqlHandle);

        // Create statement of creating the Persons table again
        std::string statement {
            "SELECT id FROM Persons;"
        };

        // Construct and execute query
        database::SQLiteQuery query{sqlHandle, statement};
        ASSERT_TRUE(query.exec());

        // Check there is another record
        EXPECT_TRUE(query.next());

        // Check there is no other record
        EXPECT_FALSE(query.next());
}



/**
 * SQLiteQuery.bindValue() Test 
 */

TEST_F(SQLiteHandleTest, SQLiteQueryClassBindValue) {
        // Add another person to databaseTrue
        std::string insertStmt {
            "INSERT INTO Persons ("
                "name,"
                "age"
            ") VALUES ("
                "?,"
                "? "
            ");"
        };

        database::SQLiteQuery insertQuery {sqlHandle, insertStmt};

        // Bind values to query
        insertQuery.bindValue(0, p2.name);
        insertQuery.bindValue(1, p2.age);

        // Execute query
        insertQuery.exec();

        // Read persons from database, and look for binded values
        std::string statement {
            "SELECT name, age FROM Persons;"
        };

        // Construct and execute query
        database::SQLiteQuery query{sqlHandle, statement};
        ASSERT_TRUE(query.exec() && query.next()); // go to p2

        std::string storedName {query.value(0).toString()};
        int storedAge {query.value(1).toInt()};

        // Compare values
        EXPECT_EQ(storedName, p2.name);
        EXPECT_EQ(storedAge,  p2.age);
}

// TODO: bindNull test



/**
 * SQLiteQuery.lastInsertId() Test 
 */

TEST_F(SQLiteHandleTest, SQLiteQueryClassLastInsertId) {
        // Add another person to databaseTrue
        std::string insertStmt {
            "INSERT INTO Persons ("
                "name,"
                "age"
            ") VALUES ("
                "\'" + p2.name + "\',"
                     + std::to_string(p2.age) + 
            ");"
        };

        database::SQLiteQuery insertQuery {sqlHandle, insertStmt};
        insertQuery.exec();

        // Get last insertion id
        p2.id = insertQuery.lastInsertId();  

        // Select the id on the database from this new person 
        std::string statement {
            "SELECT id FROM Persons;"
        };
        database::SQLiteQuery query {sqlHandle, statement};
        query.exec();
        query.next();  // Skip p1

        int storedId = query.value(0).toInt();

        // Check these two ids are equal
        EXPECT_EQ(storedId, p2.id);
}




}  // namespace 
