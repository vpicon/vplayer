/**
 * LibrarySQLiteDB_updaters.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB updater methods.
 *
 */

#include "LibrarySQLiteDB.h"


namespace database {


// TODO: is a stub
void LibrarySQLiteDB::updatePlaylistName() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::updateTrackOrderInPlaylist() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::updateTrackMetadata() {
    return;
}



// TODO: is a stub
void LibrarySQLiteDB::updateTrackPlaylistPosition() {
    return;
}



bool LibrarySQLiteDB::updateAlbum(Album &album) {
    // Prepare update statement with artist fields
    std::string statement {
        "UPDATE Albums"
        "SET "
            "title = ?, "
            "artistId = ?, "
            "year = ?,"
            "imageSource = ? "
        "WHERE "
            "id = ?"
        ";"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, album.getTitle());
    query.bindValue(1, album.getArtist().getId());
    query.bindValue(2, album.getYear());
    query.bindValue(3, album.getImgSource());
    query.bindValue(4, album.getId());

    if (!query.exec()) {
        // TODO: error handling
        return false;
    }

    return true;
}



bool LibrarySQLiteDB::updateArtist(Artist &artist) {
    // Prepare update statement with artist fields
    std::string statement {
        "UPDATE Artists"
        "SET "
            "name = ?, "
            "imageSource = ?, "
            "bio = ? "
        "WHERE "
            "id = ?"
        ";"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artist.getName());
    query.bindValue(1, artist.getImgSource());
    query.bindValue(2, artist.getBio());
    query.bindValue(3, artist.getId());

    if (!query.exec()) {
        // TODO: error handling
        return false;
    }

    return true;
}



}  // namespace database
