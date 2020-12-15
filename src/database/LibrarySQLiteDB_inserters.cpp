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



bool LibrarySQLiteDB::insertNewArtist(Artist &artist) {
    // Check if artist with same name is already in the database
    if (existsArtist(artist.getName()) {
        // Update given @artist id by the stored artist, and
        // try to update it in case some attributes changed
        int storedId = getArtistByName(artist.name());
        artist.setId(storedId);
        return updateArtist(artist);
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
