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
bool LibrarySQLiteDB::insertNewTrack(Track &track) {
    // Add album to database and get its id
    Album album {track.getAlbum()};
    if (!insertNewAlbum(album)) // sets id of album
        return false;

    int albumId = album.getId();

    // Prepare query to insert a track from the given one
    std::string statement {
        "INSERT INTO Tracks ("
            "title,"
            "albumId,"
            "additionDate,"
            "duration,"
            "source "
        ") VALUES ("
            "?,"
            "?,"
            "?,"
            "?,"
            "? "
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    query.bindValue(0, track.getTitle());
    query.bindValue(1, albumId);
    query.bindValue(2, track.getDate());
    query.bindValue(3, track.getDuration());
    query.bindValue(4, track.getSource());

    // Execute the query and set id of the track to the given by database
    if (!query.exec()) {
        // TODO: error handling
        return false;
    }

    track.setId(query.lastInsertId());

    // Add all artists to the database and link them to the track
    /*
    for (Artist &artist : track.getArtists()) {
        if (!addArtistToTrack(...))
            return false;
    }
    */

    return true;
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
    if (existsArtist(artist.getName())) {
        // Update given @artist id by the stored artist, and
        // try to update it in case some attributes changed
        int storedId = getArtistByName(artist.getName()).getId();
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
bool LibrarySQLiteDB::insertNewAlbum(Album &album) {
    return false;
}



}  // namespace database
