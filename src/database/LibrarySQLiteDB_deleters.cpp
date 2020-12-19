/**
 * LibrarySQLiteDB_deleters.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB deleter methods.
 *
 */

#include "LibrarySQLiteDB.h"


namespace database {


bool LibrarySQLiteDB::deleteTrack(const Track &track) {
    // Remove Album from track.
    deleteTrackFromAllPlaylists(track);
    
    // Remove Artists from database and its links to the track.
    for (Artist &artist : track.getArtists()) 
        deleteArtistFromTrack(track, artist);

    // Remove playlist links to track.
    deleteTrackFromAllPlaylists(track)
    
    // Romove track from Tracks table
    std::string statement {
        "DELETE FROM Tracks WHERE id = ?;"
    };
    SQLiteQuery query{_sqlHandle, statement};
    query.bindValue(0, track.getId());

    if (!query.exec())
        return false;
    
    return true;
}



// TODO: is a stub
bool LibrarySQLiteDB::deleteTrackFromPlaylist(Playlist &playlist, int pos) {
    return false;
}



// TODO: is a stub
void LibrarySQLiteDB::deletePlaylist() {
    return;
}



// TODO: is a stub
bool LibrarySQLiteDB::deleteTrackFromAllPlaylists(const Track &track) {
    return false;
}



}  // namespace database
