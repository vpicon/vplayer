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
    removeAlbumFromTrack(track);
    
    // Remove Artists from database and its links to the track.
    for (Artist &artist : track.getArtists()) 
        removeArtistFromTrack(track, artist);

    // Remove playlist links to track.
    removeTrackFromAllPlaylists(track);
    
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
bool LibrarySQLiteDB::deletePlaylist() {
    return false;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeAlbumFromTrack(const Track &track) {
    return false;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeArtistFromTrack(const Track &track, 
                                            const Artist &artist) 
{
    return false;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeTrackFromPlaylist(Playlist &playlist, int pos) {
    return false;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeTrackFromAllPlaylists(const Track &track) {
    return false;
}



}  // namespace database
