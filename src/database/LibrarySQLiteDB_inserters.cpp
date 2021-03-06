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



bool LibrarySQLiteDB::insertNewTrack(Track &track) {
    // Add album to database and get its id
    int albumId = 0;  // defined only if track has album
    if (track.hasAlbum()) {
        Album album {track.getAlbum()};
        if (!insertNewAlbum(album)) // sets id of album
            return false;

        // Update the album of the track (id may change) and get its new id
        track.setAlbum(album);
        albumId = album.getId();  // defined only if track has album
    }

    // Prepare query to insert a track from the given one
    std::string statement {
        "INSERT INTO Tracks ("
            "title,"
            "albumId,"
            "additionDate,"
            "duration,"
            "source "
        ") VALUES ("
            "?, "
            "?, "
            "?, "
            "?, "
            "?"
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    query.bindValue(0, track.getTitle());
    track.hasAlbum() ? query.bindValue(1, albumId) : query.bindNull(1);
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
    std::vector<Artist> updatedArtists {}; // store updated artists

    for (Artist &artist : track.getArtists()) {
        if (!addArtistToTrack(artist, track))
            return false;  // failure

        updatedArtists.push_back(artist);
    }
    track.setArtists(updatedArtists);

    return true;
}



bool LibrarySQLiteDB::insertNewPlaylist(Playlist &playlist) {
    // Error checking
    if (existsPlaylist(playlist.getName()))
        return false;

    // Prepare query to insert a playlist to db from the given one
    std::string statement {
        "INSERT INTO Playlists ("
            "name,"
            "imageSource "
        ") VALUES ("
            "?, "
            "?"
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    query.bindValue(0, playlist.getName());
    query.bindValue(1, playlist.getImgSource());

    // Execute the query and set id of the track to the given by database
    if (!query.exec()) {
        // TODO: error handling
        return false;
    }

    playlist.setId(query.lastInsertId());
    return true;
}



bool LibrarySQLiteDB::addTrackToPlaylist(Track &track, 
                                         Playlist &playlist, 
                                         int pos) 
{
    // Update positions of all tracks in the given playlist, 
    // which are after the given position.
    if (!incrementPlaylistPositions(playlist, pos))
        return false;  // failure
    
    
    // Add entry (trackId, artistId) to TracksArtists table
    std::string statement {
        "INSERT INTO PlaylistsTracks ("
            "trackId, "
            "playlistId, "
            "position"
        ") VALUES ("
            "?, "
            "?, "
            "?"
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    query.bindValue(0, track.getId());
    query.bindValue(1, playlist.getId());
    query.bindValue(2, pos); 

    if (!query.exec())  // TODO: error handling
        return false;

    playlist.addTrack(track, pos);

    return true;
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
            "name, "
            "imageSource, "
            "bio"
        ") VALUES ("
            "?, "
            "?, "
            "?"
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

    // Check if album with same title and artistId is already in the database
    if (existsAlbum(album.getTitle(), artist.getId())) {
        // Update given @album id by the stored album, and try to 
        // update the stored one in case some attributes changed.
        Album storedAlbum = getAlbumByTitleAndArtist(album.getTitle(), artist.getId());
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



bool LibrarySQLiteDB::addArtistToTrack(Artist &artist, Track &track) {
    // Try to add artist to the database (may already be there)
    if (!insertNewArtist(artist))  // TODO: error handling
        return false;

    // Add entry (trackId, artistId) to TracksArtists table
    std::string statement {
        "INSERT INTO TracksArtists ("
            "trackId, "
            "artistId "
        ") VALUES ("
            "?, "
            "? "
        ");"
    };
    SQLiteQuery query {_sqlHandle, statement};

    query.bindValue(0, track.getId());
    query.bindValue(1, artist.getId());

    if (!query.exec())  // TODO: error handling
        return false;

    return true;
}



}  // namespace database
