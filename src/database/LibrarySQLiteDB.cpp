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



LibrarySQLiteDB::LibrarySQLiteDB(std::string dbName) 
    : _dbName {dbName},
      _sqlHandle{_dbName}
     
{
    // Database info of tables
    _trackFields = "tr.id, "
                   "tr.title, "
                   "tr.albumId, "
                   "tr.genre, "
                   "tr.duration, "
                   "tr.additionDate, "
                   "tr.source, "
                   "tr.type ";

    _artistFields = "ar.id, "
                    "ar.name, "
                    "ar.imgSource, "
                    "ar.bio ";

    _albumFields = "al.id, "
                   "al.title, "
                   "al.artistId, "
                   "al.year, "
                   "al.imgSource ";

    _playlistFields = "pl.id, "
                      "pl.title, "
                      "pl.imgSource ";

    // Create the entire tables of the database
    createTables();
}



LibrarySQLiteDB::~LibrarySQLiteDB() 
{
    sqlite3_close(_pDB);
}



bool createTables() {
    // TODO: Check the tables are not already created
    // if (tables do not exist)
        // return false;
    
    // Call subroutines to create the different tables
    void createTableTracks();
    void createTableArtists();
    void createTableTracksArtists();
    void createTableAlbums();
    void createTablePlaylists();
    void createTableTracksPlaylists();

    return true;
}



void createTableTracks() {
    return;
}

void createTableArtists() {
    return;
}

void createTableTracksArtists() {
    return;
}

void createTableAlbums() {
    return;
}

void createTablePlaylists() {
    return;
}

void createTableTracksPlaylists() {
    return;
}






}  // namespace database
