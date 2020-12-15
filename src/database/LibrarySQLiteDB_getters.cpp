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
void LibrarySQLiteDB::getTrack() {
    return;
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
    query.bindValue(1, artistName);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRow();
}



}  // namespace database
