/**
 * LibrarySQLiteDB_inserters.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB inserter methods.
 *
 */

#include "LibrarySQLiteDB.h"


namespace database {


// TODO: is a stub
void LibrarySQLiteDB::insertNewTrack() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::insertNewPlaylist() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::insertTrackToPlaylist() {
    return;
}



// TODO: is a stub
bool LibrarySQLiteDB::insertNewArtist(Artist &artist) {
    // Check if the artist is already in the database
    if (false /* TODO: existsArtist(artist.getName() */) {
        // TODO:
        // Get stored artist id
        // Update given @artist id by the retrieved one
        return false;
    }

    // Prepare insert statement
    std::string statement {
        "INSERT INTO Artists ("
            "name,"
            "imageSource,"
            "bio"
        ") VALUES ("
            "?,"
            "?,"
            "? "
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Bind the @artist values to the query
    query.bindValue(0, artist.getName());
    query.bindValue(1, artist.getImgSource());
    query.bindValue(2, artist.getBio());
    
    // Execute insert query
    if (!query.exec()) // TODO: error handling
        return false;

    // Set the id of @artist by the given id in the database
    artist.setId(query.lastInsertId());

    return true;
}



// TODO: is a stub
bool LibrarySQLiteDB::insertNewAlbum() {
    return false;
}



}  // namespace database
