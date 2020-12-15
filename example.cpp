#include "database/LibrarySQLiteDB.h"
#include "database/Artist.h"

#include <iostream>
#include <string>

int main() {
    std::string dbName {"hola.db"};
    database::LibrarySQLiteDB db {dbName};

    // Artist 1
    database::Artist artist{"Paul Desmond", 
                            "/home/vic/Pictures/paul_desmond.png", 
                            "A nice saxophonist..."};
    db.insertNewArtist(artist);
    std::cout << artist << std::endl;

    // Artist 2
    database::Artist artist2{"Bill Evans", 
                            "evans.png", 
                            "Even nicer pianist..."};
    db.insertNewArtist(artist2);
    std::cout << artist2 << std::endl;

    return 0;
}
