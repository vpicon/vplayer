#include "database/LibrarySQLiteDB.h"

#include <string>

int main() {
    std::string dbName {"hola.db"};
    database::LibrarySQLiteDB {dbName};

    return 0;
}
