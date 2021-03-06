/**
 * LibrarySQLiteDB.cpp
 *
 * Module: database 
 *
 * Implements LibrarySQLiteDB databse creation, destruction and 
 * configuration.
 *
 */

#include "LibrarySQLiteDB.h"

#include <stdexcept>


namespace database {



LibrarySQLiteDB::LibrarySQLiteDB(std::string dbName) 
    : _sqlHandle{dbName},
      _dbName{dbName}
{
    // Database info of tables
    _trackFields = "tr.id, "
                   "tr.title, "
                   "tr.albumId, "
                   // "tr.genre, "
                   "tr.additionDate, "
                   "tr.duration, "  // in seconds
                   // "tr.type, "
                   "tr.source ";

    _artistFields = "ar.id, "
                    "ar.name, "
                    "ar.imageSource, "
                    "ar.bio ";

    _albumFields = "al.id, "
                   "al.title, "
                   "al.artistId, "
                   "al.year, "
                   "al.imageSource ";

    _playlistFields = "pl.id, "
                      "pl.name, "
                      "pl.imageSource ";

    // Create the entire tables of the database
    createTables();
}



LibrarySQLiteDB::~LibrarySQLiteDB() 
{
}



bool LibrarySQLiteDB::createTables() {
    // TODO: Check the tables are not already created
    // if (tables do not exist)
        // return false;

    // Configure the db management
    configureDB();
    
    // Call subroutines to create the different tables
    createTableTracks();
    createTableArtists();
    createTableTracksArtists();
    createTableAlbums();
    createTableAlbumsTracks();
    createTablePlaylists();
    createTablePlaylistsTracks();

    return true;
}



void LibrarySQLiteDB::configureDB() {
    // Add support for foreign keys.
    std::string statement {
        "PRAGMA foreign_keys = ON;"
    };
    SQLiteQuery query {_sqlHandle, statement};
    query.exec();
}



bool LibrarySQLiteDB::createTableTracks() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS Tracks ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
            "title TEXT NOT NULL,"
            "albumId INTEGER," 
            "additionDate TEXT NOT NULL,"  // TODO: change to a type to code - decode
            "duration INTEGER,"    // duration of track in seconds
            "source TEXT NOT NULL,"
            "FOREIGN KEY(albumId) REFERENCES Albums ON DELETE SET NULL" // TODO: add constraint operations
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTableArtists() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS Artists ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
            "name TEXT NOT NULL,"
            "imageSource TEXT,"
            "bio TEXT,"
            "UNIQUE(name) ON CONFLICT IGNORE" // TODO: revise conflict conseqences
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTableTracksArtists() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS TracksArtists ("
            "trackId INTEGER NOT NULL,"
            "artistId INTEGER NOT NULL,"
            "UNIQUE(trackId, artistId) ON CONFLICT IGNORE," // TODO: revise conflict conseqences
            "FOREIGN KEY(trackId) REFERENCES Tracks ON DELETE CASCADE,"  // TODO: add constraint operations
            "FOREIGN KEY(artistId) REFERENCES Artists ON DELETE CASCADE" // TODO: "   "          "
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTableAlbums() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS Albums ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
            "title TEXT NOT NULL,"
            "artistId INTEGER NOT NULL,"
            "year INTEGER,"
            "imageSource TEXT,"
            "UNIQUE(title, artistId) ON CONFLICT IGNORE," // TODO: revise conflict conseqences
            "FOREIGN KEY(artistId) REFERENCES Artists" // TODO: add constraint operations
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTableAlbumsTracks() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS AlbumsTracks ("
            "trackId INTEGER NOT NULL,"
            "albumId INTEGER NOT NULL,"
            "position INTEGER NOT NULL," // position of the track in the playlist
            "UNIQUE(trackId, albumId, position) ON CONFLICT IGNORE," // TODO: revise conflict conseqences
            "FOREIGN KEY(trackId) REFERENCES Tracks," // TODO: add constraint operations
            "FOREIGN KEY(albumId) REFERENCES Albums"  // TODO: "   "          "
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTablePlaylists() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS Playlists ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
            "name TEXT NOT NULL, "
            "imageSource TEXT, "
            "UNIQUE(name) ON CONFLICT IGNORE"
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



bool LibrarySQLiteDB::createTablePlaylistsTracks() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS PlaylistsTracks ("
            "trackId INTEGER NOT NULL,"
            "playlistId INTEGER NOT NULL,"
            "position INTEGER NOT NULL," // position of the track in the playlist, starting at 0
            "UNIQUE(playlistId, position) ON CONFLICT IGNORE," // TODO: revise conflict conseqences
            "FOREIGN KEY(trackId) REFERENCES Tracks ON DELETE CASCADE,"    // TODO: add constraint operations
            "FOREIGN KEY(playlistId) REFERENCES Playlists ON DELETE CASCADE" // TODO: "   "          "
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}





}  // namespace database
