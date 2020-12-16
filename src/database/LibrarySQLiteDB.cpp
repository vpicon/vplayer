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
                   "tr.genre, "
                   "tr.duration, "
                   "tr.additionDate, "
                   "tr.source, "
                   "tr.type ";

    _artistFields = "ar.id, "
                    "ar.name, "
                    "ar.imgSource, "
                    "ar.bio ";

    _albumFields = "al.id, "
                   "al.title, "
                   "al.artistId, "
                   "al.year, "
                   "al.imgSource ";

    _playlistFields = "pl.id, "
                      "pl.title, "
                      "pl.imgSource ";

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



bool LibrarySQLiteDB::createTableTracks() {
    std::string statement {
        "CREATE TABLE IF NOT EXISTS Tracks ("
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
            "title TEXT NOT NULL,"
            "albumId INTEGER," 
            "additionDate INTEGER NOT NULL,"  // TODO: change to a type to code - decode
            "duration INTEGER,"
            // "genre TEXT," // TODO: add as a relation table (track, genre) (and add another genre table)
            "source TEXT NOT NULL,"
            "FOREIGN KEY(albumId) REFERENCES Albums" // TODO: add constraint operations
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
            "UNIQUE(trackId, artistId)," // TODO: revise conflict conseqences
            "FOREIGN KEY(trackId) REFERENCES Tracks,"  // TODO: add constraint operations
            "FOREIGN KEY(artistId) REFERENCES Artists" // TODO: "   "          "
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
            "year INTEGER NOT NULL,"
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
            "id INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE,"
            "name TEXT NOT NULL,"
            "imageSource TEXT"
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
            "position INTEGER NOT NULL," // position of the track in the playlist
            "UNIQUE(trackId, playlistId, position) ON CONFLICT IGNORE," // TODO: revise conflict conseqences
            "FOREIGN KEY(trackId) REFERENCES Tracks,"    // TODO: add constraint operations
            "FOREIGN KEY(playlistId) REFERENCES Playlists" // TODO: "   "          "
        ");"
    };

    SQLiteQuery query{_sqlHandle, statement};
    return query.exec();
}



/**
 * Creates an album object from an album containing a query row to 
 * an album with values (id, title, artistId, year, imgSource) values.
 */
Album LibrarySQLiteDB::hydrateAlbum(SQLiteQuery &query) {
    Album album {query.value(0).toInt(),      // id
                 query.value(1).toString(),   // title
         // Skip query.value(2) artistId
                 query.value(3).toInt(),      // year
                 query.value(4).toString()};  // imgSource

    // TODO: add artist to Album

    return album;
}


}  // namespace database
