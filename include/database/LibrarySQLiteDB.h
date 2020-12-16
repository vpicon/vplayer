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
    void insertNewPlaylist() override;
    void insertTrackToPlaylist() override;

    // DELETERS
    void deleteTrackFromLibrary() override {}
    void deleteTrackFromPlaylist() override {}
    void deletePlaylist() override {}
    
    // GETTERS
    void getLibraryTracks() override;
    void getPlaylistTracks() override;
    void getPlaylists() override;
    void getAlbumTracks() override;
    Track getTrack(int id) override;
    void getArtistAlbums() override;

    /**
     * Given a source file, says if there is a track in the database
     * with the given source.
     */
    bool existsTrack(std::string source);

    // UPDATERS
    void updatePlaylistName() override;
    void updateTrackOrderInPlaylist() override;
    void updateAlbumMetadata() override;
    void updateTrackMetadata() override;
    void updateTrackPlaylistPosition() override;

private:
    SQLiteHandle _sqlHandle;    // SQLite3 db handle
    const std::string _dbName;  // Database filename

    // DATABASE TABLES INFO
    std::string _trackFields;
    std::string _artistFields;
    std::string _albumFields;
    std::string _playlistFields;

    // SCHEMA BUILDERS 
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
     * Tries to add new album to the database. If no artists exists in
     * the database with the given title and artist, inserts the given 
     * one into the database and sets the id of @album by the id given 
     * by the database. 
     * If an album with the same name is already in the database, 
     * updates the id of the given @album to the id of the album in 
     * the database.
     *
     * Returns true on success, independently of adding the album
     * or not. Return false otherwise on any error.
     */
    bool insertNewAlbum(Album &album);

    void setTracksToPlaylist(Playlist &playlist);
    void setArtistsToTrack(Track &track);

    // GETTERS
    /**
     * Hydrate objects from a query containing data.
     */
    Track hydrateTrack(SQLiteQuery &query);
    Album hydrateAlbum(SQLiteQuery &query);
    Artist hydrateArtist(SQLiteQuery &query);
    Playlist hydratePlaylist(SQLiteQuery &query);

    /**
     * Returns true iff exists an artist in the database with the
     * given artistName.
     */
    bool existsArtist(std::string artistName);

    Artist getArtistByName(std::string artistName);

    // UPDATERS

    /**
     * Updates the artist stored in the database with the same id as 
     * the artist id. 
     *
     * Returns true on success. False otherwise on any errors.
     */
    bool updateArtist(Artist &artist);
};



}  // namespace database



#endif  // _VPLAYER_LIBRARY_SQLITE_DB_H
