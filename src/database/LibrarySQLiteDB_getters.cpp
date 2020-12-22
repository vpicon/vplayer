/**
 * LibrarySQLiteDB_getters.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB getter methods.
 *
 */

#include "LibrarySQLiteDB.h"

#include <string>


namespace database {



std::vector<Track> LibrarySQLiteDB::getAllTracks() {
    // Make query to retrieve all tracks
    std::string statement {
        "SELECT " + _trackFields + "FROM Tracks AS tr;"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all tracks
    std::vector<Track> tracks {};

    // Hydrate tracks while available records
    while (query.availableRecord()) {
        Track track = hydrateTrack(query);
        tracks.push_back(track);
        query.next();
    }

    return tracks;
}



Track LibrarySQLiteDB::getTrack(const int id) {
    Track track;

    // Make query to retrieve track with given id
    std::string statement {
        "SELECT " + _trackFields + "FROM Tracks AS tr "
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



std::vector<Playlist> LibrarySQLiteDB::getAllPlaylists() {
    // Make query to retrieve all playlists
    std::string statement {
        "SELECT " + _playlistFields + "FROM Playlists AS pl;"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all tracks
    std::vector<Playlist> playlists {};

    // Hydrate tracks while available records
    while (query.availableRecord()) {
        Playlist playlist = hydratePlaylist(query);
        playlists.push_back(playlist);
        query.next();
    }

    return playlists;
}



std::vector<Album> LibrarySQLiteDB::getAllAlbums() {
    // Make query to retrieve all albums
    std::string statement {
        "SELECT " + _albumFields + "FROM Albums AS al;"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all tracks
    std::vector<Album> albums {};

    // Hydrate tracks while available records
    while (query.availableRecord()) {
        Album album = hydrateAlbum(query);
        albums.push_back(album);
        query.next();
    }

    return albums;
}



std::vector<Track> LibrarySQLiteDB::getAlbumTracks(const Album &album) {
    // Make query to retrieve all tracks from album
    std::string statement {
        "SELECT " + _trackFields + "FROM Tracks AS tr "
        "WHERE tr.albumId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, album.getId());

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all tracks
    std::vector<Track> tracks {};

    // Hydrate tracks while available records
    while (query.availableRecord()) {
        Track track = hydrateTrack(query);
        tracks.push_back(track);
        query.next();
    }

    return tracks;
}



std::vector<Artist> LibrarySQLiteDB::getAllArtists() {
    // Make query to retrieve all albums
    std::string statement {
        "SELECT " + _artistFields + "FROM Artists AS ar;"
    };
    SQLiteQuery query {_sqlHandle, statement};

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all artists
    std::vector<Artist> artists {};

    // Hydrate artists while available records
    while (query.availableRecord()) {
        Artist artist = hydrateArtist(query);
        artists.push_back(artist);
        query.next();
    }

    return artists;
}



std::vector<Album> LibrarySQLiteDB::getArtistAlbums(const Artist &artist) {
    // Make query to retrieve all albums from given artist
    std::string statement {
        "SELECT " + _albumFields + "FROM Albums AS al "
        "WHERE al.artistId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artist.getId());

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Vector of all tracks
    std::vector<Album> albums {};

    // Hydrate tracks while available records
    while (query.availableRecord()) {
        Album album = hydrateAlbum(query);
        albums.push_back(album);
        query.next();
    }

    return albums;
}



Track LibrarySQLiteDB::hydrateTrack(SQLiteQuery &query) {
    Track track; 

    track.setId(query.value(0).toInt());
    track.setTitle(query.value(1).toString());
    track.setDate(query.value(3).toString());
    track.setDuration(query.value(4).toInt());
    track.setSource(query.value(5).toString());

    // Set album to track, if it has one
    if (!query.value(2).isNull()) {
        int artistId = query.value(2).toInt(); 
        setAlbumToTrack(track, artistId);
    }

    // Add all artists to the track
    setArtistsToTrack(track);

    return track;
}



Album LibrarySQLiteDB::hydrateAlbum(SQLiteQuery &query) {
    Album album; 

    album.setId(query.value(0).toInt());
    album.setTitle(query.value(1).toString());
    album.setYear(query.value(3).toInt());
    album.setImgSource(query.value(4).toString());

    // Get Artist from artistId and link it to tables
    int artistId = query.value(2).toInt();
    setArtistToAlbum(album, artistId);

    return album;
}



Artist LibrarySQLiteDB::hydrateArtist(SQLiteQuery &query) {
    Artist artist; 

    artist.setId(query.value(0).toInt());
    artist.setName(query.value(1).toString());
    artist.setImgSource(query.value(2).toString());
    artist.setBio(query.value(3).toString());

    return artist;
}



Playlist LibrarySQLiteDB::hydratePlaylist(SQLiteQuery &query) {
    Playlist playlist; 

    playlist.setId(query.value(0).toInt());
    playlist.setName(query.value(1).toString());
    playlist.setImgSource(query.value(2).toString());

    // Add all tracks to the playlist
    setTracksToPlaylist(playlist);

    return playlist;
}



void LibrarySQLiteDB::setAlbumToTrack(Track &track, const int albumId) {
    // Retrieve album fields with album id
    std::string statement {
        "SELECT " + _albumFields + " FROM Albums AS al "
        "WHERE al.id = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, albumId);

    if (!query.exec())
        /* TODO: error handling */;

    // Add artist to album if one found
    if (query.availableRecord()) {
        Album album = hydrateAlbum(query);
        track.setAlbum(album);
    }
}



void LibrarySQLiteDB::setArtistsToTrack(Track &track) {
    // Create empty list of artists
    std::vector<Artist> artists {};

    // Retrieve artists linked to given track
    std::string statement {
        "SELECT " + _artistFields + " "
        "FROM Artists AS ar, TracksArtists AS ta "
        "WHERE ar.id = ta.artistId AND "
              "ta.trackId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, track.getId());

    if (!query.exec())
        /* TODO: error handling */;

    // Add retrieve artists and add them to list
    while (query.availableRecord()) {
        Artist artist = hydrateArtist(query);
        artists.push_back(artist);
        query.next();
    }

    // Set the artists to the track
    track.setArtists(artists);
}



void LibrarySQLiteDB::setArtistToAlbum(Album &album, const int artistId) {
    // Retrieve artist fields with artist id
    std::string statement {
        "SELECT " + _artistFields + " FROM Artists AS ar "
        "WHERE ar.id = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artistId);

    if (!query.exec())
        /* TODO: error handling */;

    // Add artist to album if one found
    if (query.availableRecord()) {
        Artist artist = hydrateArtist(query);
        album.setArtist(artist);
    }

    return;
}



void LibrarySQLiteDB::setTracksToPlaylist(Playlist &playlist) {
    // Create empty list of artists
    std::vector<Track> tracks {};

    // Retrieve artists linked to given track
    std::string statement {
        "SELECT " + _trackFields + " "
        "FROM Tracks AS tr, PlaylistsTracks AS pt "
        "WHERE tr.id = pt.trackId AND "
              "pt.playlistId = ? "
        "ORDER BY pt.position ASC;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, playlist.getId());

    if (!query.exec())
        /* TODO: error handling */;

    // Add retrieve artists and add them to list
    while (query.availableRecord()) {
        Track track = hydrateTrack(query);
        tracks.push_back(track);
        query.next();
    }

    // Set the artists to the track
    playlist.setTracks(tracks);
}



bool LibrarySQLiteDB::existsArtist(const std::string &artistName) {
    std::string statement {
        "SELECT id FROM Artists "
        "WHERE Artists.name = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artistName);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRecord();
}



bool LibrarySQLiteDB::existsAlbum(const std::string &albumTitle, 
                                  const int artistId) 
{
    std::string statement {
        "SELECT id FROM Albums AS al "
        "WHERE al.title = ? AND al.artistId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, albumTitle);
    query.bindValue(1, artistId);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRecord();
}



bool LibrarySQLiteDB::existsPlaylist(const std::string &playlistName) {
    std::string statement {
        "SELECT id FROM Playlists AS pl "
        "WHERE pl.name = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, playlistName);
    
    if (!query.exec()) 
        /* TODO: some debug */;
        
    return query.availableRecord();
}



Artist LibrarySQLiteDB::getArtistByName(const std::string &artistName) {
    Artist artist;

    // Make query to retrieve track with given id
    std::string statement {
        "SELECT " + _artistFields + " FROM Artists AS ar "
        "WHERE ar.name = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, artistName);

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Check if there is some record for the given query and get it
    if (query.availableRecord()) 
        artist = hydrateArtist(query);

    return artist;
}



Album LibrarySQLiteDB::getAlbumByTitleAndArtist(const std::string &albumTitle, 
                                                const int artistId) 
{
    Album album;

    // Make query to retrieve track with given id
    std::string statement {
        "SELECT " + _albumFields + " FROM Albums AS al "
        "WHERE al.title = ? AND al.artistId = ?;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.bindValue(0, albumTitle);
    query.bindValue(1, artistId);

    // Execute query
    if (!query.exec())
        /* TODO: error handling */;

    // Check if there is some record for the given query and get it
    if (query.availableRecord()) 
        album = hydrateAlbum(query);

    return album;
}




}  // namespace database
