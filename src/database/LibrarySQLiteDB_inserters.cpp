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
        // Update given @artist id by the stored artist, and try to 
        // update the stored one in case some attributes changed.
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



bool LibrarySQLiteDB::insertNewAlbum(Album &album) {
    // Get the associated artist of the album and try to add it to 
    // database, setting thus its id.
    Artist artist = album.getArtist();
    if (!insertNewArtist(artist))  // TODO: error handling
        return false;

    // Update the artist of the album
    album.setArtist(artist);

    // Check if album with same name and artistId is already in the database
    if (existsAlbum(album.getName(), album.getId())) {
        // Update given @album id by the stored album, and try to 
        // update the stored one in case some attributes changed.
        Album storedAlbum = getAlbumByNameAndArtist(album.getName(), artist.getId());
        album.setId(storedAlbum.getId());
        return updateAlbum(album);
    }

    // Prepare insert statement
    std::string statement {
        "INSERT INTO Albums ("
            "title,"
            "artistId,"
            "year,"
            "imageSource"
        ") VALUES ("
            "?,"
            "?,"
            "?,"
            "? "
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Bind the album values and artist id to the query
    query.bindValue(0, album.getTitle());
    query.bindValue(1, artist.getId());
    query.bindValue(2, album.getYear());
    query.bindValue(3, album.getImgSource());
    
    // Execute insert query
    if (!query.exec()) // TODO: error handling
        return false;

    // Set the id of album by the given id in the database
    album.setId(query.lastInsertId());

    return true;
}



}  // namespace database
