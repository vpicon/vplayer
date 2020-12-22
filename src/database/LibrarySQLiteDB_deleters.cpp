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
    if (track.hasAlbum())
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



bool LibrarySQLiteDB::deletePlaylist(const Playlist &playlist) {
    // Remove all tracks linked to playlist.
    removeAllTracksFromPlaylist(playlist);

    // Remove playlist from Playlists table
    std::string statement {
        "DELETE FROM Playlists WHERE id = ?;"
    };
    SQLiteQuery query{_sqlHandle, statement};
    query.bindValue(0, playlist.getId());

    if (!query.exec())
        return false;
    
    return true;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeTrackFromPlaylist(Playlist &playlist, int pos) {
    return false;
}



bool LibrarySQLiteDB::deleteArtist(const Artist &artist) {
    // Remove artist from Artists table
    std::string statement {
        "DELETE FROM Artists WHERE id = ?;"
    };
    SQLiteQuery query{_sqlHandle, statement};
    query.bindValue(0, artist.getId());

    if (!query.exec())
        return false;
    
    return true;
}



bool LibrarySQLiteDB::deleteAlbum(const Album &album) {
    // Delete album's artist
    deleteArtist(album.getArtist());

    // Romove artist from Artists table
    std::string statement {
        "DELETE FROM Albums WHERE id = ?;"
    };
    SQLiteQuery query{_sqlHandle, statement};
    query.bindValue(0, album.getId());

    if (!query.exec())
        return false;
    
    return true;
}



bool LibrarySQLiteDB::removeAlbumFromTrack(const Track &track) {
    // Check if there are more tracks linked to the given track's album
    std::string statement {
        "SELECT id FROM Tracks "
        "WHERE albumId = ?;"
    };
    SQLiteQuery query{_sqlHandle, statement};
    query.bindValue(0, track.getAlbum().getId());

    if (!query.exec())
        return false;

    int numResults = 0; // count number of tracks having such albumId
    while (query.availableRecord()) {
        numResults++;
        query.next();
    }
    
    if (numResults <= 1) { // only the given track linked to such album
        deleteAlbum(track.getAlbum());         
    }

    return true;
}



bool LibrarySQLiteDB::removeArtistFromTrack(const Track &track, 
                                            const Artist &artist) 
{
    // Prepare statement to delete links between artists and track
    std::string statement {
        "DELETE FROM TracksArtists "
        "WHERE trackId  = ? AND "
              "artistId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, track.getId());
    query.bindValue(1, artist.getId());

    if (!query.exec())
        return false;

    // Check if artist still used by other tracks, otherwise delete it
    std::string statement2 {
        "SELECT 1 FROM TracksArtists "
        "WHERE artistId = ?;"
    };
    SQLiteQuery query2 {_sqlHandle, statement2};
    query2.bindValue(0, artist.getId());
    if (!query2.exec())
        return false;

    // Delete artist if not used
    if (!query2.availableRecord()) {
        // Delete orphan artist
        deleteArtist(artist);
    }

    return true;
}



// TODO: is a stub
bool LibrarySQLiteDB::removeTrackFromAllPlaylists(const Track &track) {
    return false;
}



bool LibrarySQLiteDB::removeAllTracksFromPlaylist(const Playlist &playlist) {
    // Prepare statement to delete links between artists and track
    std::string statement {
        "DELETE FROM PlaylistsTracks "
        "WHERE playlistId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, playlist.getId());

    if (!query.exec())
        return false;

    return true;
}



}  // namespace database
