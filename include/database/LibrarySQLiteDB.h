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

#include <string>
#include <sqlite3.h>


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
    void insertTrackToLibrary() override {}
    void insertTrackToPlaylist() override {}
    void insertPlaylist() override {}

    // DELETERS
    void deleteTrackFromLibrary() override {}
    void deleteTrackFromPlaylist() override {}
    void deletePlaylist() override {}
    
    // GETTERS
    void getLibraryTracks() override {}
    void getPlaylistTracks() override {}
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
    sqlite3 *_pDB;  // SQLite db handle
    const std::string _dbName;  // Database filename (UTF-8)

    // DATABASE TABLES INFO
    std::string _trackFields;
    std::string _artistFields;
    std::string _albumFields;
    std::string _playlistFields;

    // HELPER METHODS
    /**
     * Creates all the tables of the database if they do not exist
     * already.
     */
    void createTables();
    void createTableTracks();
    void createTableArtists();
    void createTableTracksArtists();
    void createTableAlbums();
    void createTablePlaylists();
    void createTableTracksPlaylists();
};



}  // namespace database



#endif  // _VPLAYER_LIBRARY_SQLITE_DB_H
