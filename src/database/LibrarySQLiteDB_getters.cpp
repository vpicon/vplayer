/**
 * LibrarySQLiteDB_getters.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB getter methods.
 *
 */

#include "LibrarySQLiteDB.h"


namespace database {



// TODO: is a stub
void LibrarySQLiteDB::getLibraryTracks() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::getPlaylistTracks() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::getPlaylists() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::getAlbumTracks() {
    return;
}



// TODO: is a stub
Track LibrarySQLiteDB::getTrack(int id) {
    Track track;

    // Make query to retrieve track with given id
    std::string statement {
        "SELECT " + _trackFields + "FROM Tracks AS tr"
        "WHERE id = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, id);

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;
    // Check if there is some record for the given query and get it
    if (query.availableRecord()) 
        track = hydrateTrack(query);

    return track;
}



// TODO: is a stub
void LibrarySQLiteDB::getAuthorAlbums() {
    return;
}



// TODO: is a stub
bool LibrarySQLiteDB::existsArtist(std::string artistName) {
    std::string statement {
        "SELECT id FROM Artists"
        "WHERE Artists.name = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artistName);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRecord();
}



}  // namespace database
