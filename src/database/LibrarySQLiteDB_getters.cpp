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
void LibrarySQLiteDB::getArtistAlbums() {
    return;
}



Track LibrarySQLiteDB::hydrateTrack(SQLiteQuery &query) {
    return Track{};
}



Album LibrarySQLiteDB::hydrateAlbum(SQLiteQuery &query) {
    Album album; 

    album.setId(query.value(0).toInt());
    album.setTitle(query.value(1).toString());
    album.setYear(query.value(3).toInt());
    album.setImgSource(query.value(4).toString());

    // TODO:
    // Get Artist from artistId  and link it to tables
    // int artistId = query.value(2).toInt;

    return album;
}



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



bool LibrarySQLiteDB::existsAlbum(std::string albumTitle, int artistId) {
    std::string statement {
        "SELECT id FROM Albums AS al"
        "WHERE "
            "al.title    = ?,"
            "al.artistId = ? "
        ";"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, albumTitle);
    query.bindValue(1, artistId);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRecord();
}



// TODO: is a stub
Artist LibrarySQLiteDB::getArtistByName(std::string artistName) {
    return Artist{};
}



// TODO: is a stub
Album LibrarySQLiteDB::getAlbumByTitleAndArtist(std::string albumTitle, int artistId) {
    return Album{};
}




}  // namespace database
