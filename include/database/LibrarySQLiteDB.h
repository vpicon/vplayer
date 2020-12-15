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
    /**
     * Adds new track to the library.
     */
    void insertNewTrack() override {}
    void insertNewPlaylist() override {}
    void insertTrackToPlaylist() override {}

    // DELETERS
    void deleteTrackFromLibrary() override {}
    void deleteTrackFromPlaylist() override {}
    void deletePlaylist() override {}
    
    // GETTERS
    void getLibraryTracks() override {}
    void getPlaylistTracks() override {}
    void getPlaylists() override {}
    void getAlbumTracks() override {}
    void getTrack() override {}
    void getAuthorAlbums() override {}

    // UPDATERS
    void updatePlaylistName() override {}
    void updateTrackOrderInPlaylist() override {}
    void updateAlbumMetadata() override {}
    void updateTrackMetadata() override {}
    void updateTrackPlaylistPosition() override {}

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
     * already. Returns if it created the tables or not.
     */
    bool createTables();
    bool createTableTracks();
    bool createTableArtists();
    bool createTableTracksArtists();
    bool createTableAlbums();
    bool createTablePlaylists();
    bool createTablePlaylistsTracks();

    // GETTERS : OBJECT HYRDRATORS
    void setTracksToPlaylist(Playlist &playlist);
    void setArtistsToTrack(Track &track);
    /**
     * Hydrate objects from a query containing data.
     */
    Track hydrateTrack(SQLiteQuery &query);
    Album hydrateAlbum(SQLiteQuery &query);
    Artist hydrateArtist(SQLiteQuery &query);
    Playlist hydratePlaylist(SQLiteQuery &query);

    // INSERTERS
    void insertNewArtist();
    void insertNewAlbum();
};



}  // namespace database



#endif  // _VPLAYER_LIBRARY_SQLITE_DB_H
