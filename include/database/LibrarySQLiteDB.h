/**
 * LibrarySQLiteDB.h
 *
 * Module: database 
 *
 * Defines LibrarySQLiteDB abstract class interface.
 *
 */

#ifndef _VPLAYER_LIBRARY_SQLITE_DB_H
#define _VPLAYER_LIBRARY_SQLITE_DB_H


#include "LibraryDB.h"
#include "SQLiteHandle.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"
#include "Playlist.h"

#include <string>


namespace database {



/**
 * Manages the Library database via an SQL dbm with SQLite. Implements
 * the LibraryDB interface.
 */
class LibrarySQLiteDB : public LibraryDB {
    /**
     * TODO: Class invariants
     */
public:
    LibrarySQLiteDB(std::string dbname);
    ~LibrarySQLiteDB();

    // INSERTERS
    bool insertNewTrack(Track &track) override;
    bool insertNewPlaylist(Playlist &playlist) override;
    bool addTrackToPlaylist(Track &track, Playlist &playlist, int pos) override;
    
    // GETTERS
    std::vector<Track> getAllTracks() override;
    Track getTrack(const int id) override;
    std::vector<Playlist> getAllPlaylists() override;
    std::vector<Album> getAllAlbums() override;
    std::vector<Track> getAlbumTracks(const Album &album) override;
    std::vector<Artist> getAllArtists() override;
    std::vector<Album> getArtistAlbums(const Artist &artist) override;
    bool existsTrack(std::string source);

    // UPDATERS
    void updatePlaylistName() override;
    void updateTrackOrderInPlaylist() override;
    bool updateAlbum(Album &album) override;
    bool updateArtist(Artist &artist) override;
    void updateTrackMetadata() override;
    void updateTrackPlaylistPosition() override;

    // DELETERS
    bool deleteTrack(const Track &track) override;
    bool deletePlaylist(const Playlist &playlist) override;
    bool removeTrackFromPlaylist(Playlist &playlist, int pos) override;

private:
    SQLiteHandle _sqlHandle;    // SQLite3 db handle
    const std::string _dbName;  // Database filename

    // DATABASE TABLES INFO
    std::string _trackFields;
    std::string _artistFields;
    std::string _albumFields;
    std::string _playlistFields;

    // SCHEMA BUILDERS 
    
    void configureDB();
    /**
     * Creates all the tables of the database if they do not exist
     * already. 
     * 
     * Returns false on any failure, true otherwise.
     */
    bool createTables();
    bool createTableTracks();
    bool createTableArtists();
    bool createTableTracksArtists();
    bool createTableAlbums();
    bool createTableAlbumsTracks();
    bool createTablePlaylists();
    bool createTablePlaylistsTracks();

    // INSERTERS
    /**
     * Tries to add new artist to the database. If no artists exists in
     * the database with the given name, inserts the given one into the
     * database and sets the id of @artist by the id given by the database. 
     * If an artist with the same name is already in the database, 
     * updates the id of the given @artist to the id of the artist in 
     * the database.
     *
     * Returns true on success, independently of adding the artist
     * or not. Return false otherwise on any error.
     */
    bool insertNewArtist(Artist &artist);
    /**
     * Tries to add new album to the database. If no album exists in
     * the database with the given title and artist, inserts the given 
     * one into the database and sets the id of @album by the id given 
     * by the database. 
     * If an album with the same name is already in the database, 
     * updates the id of the given @album to the id of the album in 
     * the database.
     *
     * The artist associated with the album is also added to the database
     * and its id is set to the id given by the database.
     *
     * Returns true on success, independently of adding the album
     * or not. Return false otherwise on any error.
     */
    bool insertNewAlbum(Album &album);


    /**
     * Given a potentially new artist, and a track previously added to
     * the database, adds the artist to the database and links the 
     * track to the artist.
     *
     * When adding the artist to the database, its id is set to the
     * id given by the database.
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool addArtistToTrack(Artist &artist, Track &track);

    // GETTERS
    /**
     * Hydrate objects from a query containing data.
     */
    Track hydrateTrack(SQLiteQuery &query);
    /**
     * Creates an album object from a query record containing an album 
     * with values (id, title, artistId, year, imgSource) values.
     */
    Album hydrateAlbum(SQLiteQuery &query);
    /**
     * Creates an artist object from a query record containing an artist
     * with values (id, name, imageSource, bio) values.
     */
    Artist hydrateArtist(SQLiteQuery &query);
    /**
     * Hydrate objects from a query containing data.
     */
    Playlist hydratePlaylist(SQLiteQuery &query);

    /**
     * Gets the album associated to the track from the database, and 
     * sets it to the given track object.
     */
    void setAlbumToTrack(Track &track, const int albumId);
    /*
     * Given a track with an id from the database, gets the artist 
     * associated to the track from the database, and sets it to the 
     * given track object.
     */
    void setArtistsToTrack(Track &track);
    /**
     * Gets the artist associated to the album from the database, and 
     * sets it to the given album object.
     */
    void setArtistToAlbum(Album &album, const int artistId);
    /*
     * Given a playlist with an id from the database, gets the tracks 
     * associated to such playlist from the database.
     */
    void setTracksToPlaylist(Playlist &playlist);

    /**
     * Returns true iff exists an artist in the database with the
     * given artistName.
     */
    bool existsArtist(const std::string &artistName);
    /**
     * Returns true iff exists an album in the database with the
     * given albumTitle and artistId.
     */
    bool existsAlbum(const std::string &albumTitle, const int artistId);
    /**
     * Returns true iff exists a playlist in the database with the
     * given playlistName.
     */
    bool existsPlaylist(const std::string &playlistName);

    /**
     * Given a string referring to a name of an artist, tries to 
     * retrieve an artist with given name from database.
     * If not found, returns empty artist (with empty name).
     */
    Artist getArtistByName(const std::string &artistName);
    /**
     * Given a string referring to a name of an album and an artist id, 
     * tries to retrieve an album with given fields from database.
     * If not found, returns empty album (with empty title).
     */
    Album getAlbumByTitleAndArtist(const std::string &albumTitle, const int artistId);

    // DELETERS
    /**
     * Given an artist object, deletes it from the database.
     *
     * Should not be called directly but after removing any links from 
     * tracks to it.
     */
    bool deleteArtist(const Artist &artist);
    /**
     * Given an album object, deletes it from the database, deleting
     * also its artist.
     *
     * Should not be called directly but after removing any links from 
     * tracks to it.
     */
    bool deleteAlbum(const Album &album);

    /**
     * Given a track previously added to the database, removes the 
     * track's album from the database if there are no more tracks 
     * in the database linked to such album.
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool removeAlbumFromTrack(const Track &track);
    /**
     * Given a track and artist, both previously added to the database,
     * removes the link between the artist and the track, and removes
     * artist from the database if there are no more tracks in the 
     * database linked to such artist.
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool removeArtistFromTrack(const Track &track, const Artist &artist);
    /**
     * Given a track previously added to the database, removes its links
     * with all the playlists in the database.
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool removeTrackFromAllPlaylists(const Track &track);
    /**
     * Given a playlist previously added to the database, removes the 
     * links between all tracks and the playlist. 
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool removeAllTracksFromPlaylist(const Playlist &playlist);

    // UPDATERS
    /**
     * Given a playlist previously added to the database, increments the 
     * position number of the tracks with position >= startingPos.
     *
     * Should not be called directly, but from a playlist inserter or 
     * updater method.
     *
     * Returns false on any error or failure, true otherwise.
     */
    bool incrementPlaylistPositions(Playlist &playlist, int startingPos);
};



}  // namespace database



#endif  // _VPLAYER_LIBRARY_SQLITE_DB_H
