/**
 * LibraryDB.h
 *
 * Module: database 
 *
 * Defines LibraryDB abstract class interface.
 *
 */

#ifndef _VPLAYER_LIBRARY_DB_H
#define _VPLAYER_LIBRARY_DB_H



namespace database {



class LibraryDB {
public:
    // Virtual destructor in polymorphic base classes 
    virtual ~LibraryDB();

    // INSERTERS
    /**
     * Adds a new song to the library.
     */
    virtual void insertTrackToLibrary() = 0;
    /**
     * Given a playlist and the given track object, inserts it to the playlist.
     */
    virtual void insertTrackToPlaylist() = 0;
    /**
     * Creates a new empty playlist with given name.
     */
    virtual void insertPlaylist() = 0;

    // DELETERS
    /**
     * Removes song from the entire library, and from all playlists referencing 
     * it.
     */
    virtual void deleteTrackFromLibrary() = 0; 
    /**
     * Removes song from the given playlist, but the song remains in the library.
     */
    virtual void deleteTrackFromPlaylist() = 0; 
    /**
     * Removes the entire playlist, with all the song references in it. But the 
     * songs still remain in the library.
     */
    virtual void deletePlaylist() = 0; 
    
    // GETTERS
    /**
     * Gives all the tracks in the library.
     */
    virtual void getLibraryTracks() = 0;
    /**
     * Gives all the tracks in a given playlist.
     */
    virtual void getPlaylistTracks() = 0;
    /**
     * Gives all the tracks in a given album.
     */
    virtual void getAlbumTracks() = 0;
    virtual void getTrack() = 0;
    /**
     * Gives all the tracks of a given author.
     */
    virtual void getAuthorAlbums() = 0;

    // UPDATERS
    /**
     * Changes the name of a given playlist.
     */
    virtual void updatePlaylistName() = 0;
    /**
     * Changes the order of a track in a playlist.
     */
    virtual void updateTrackOrderInPlaylist() = 0;
    /**
     * Changes metadata of a given album.
     */
    virtual void updateAlbumMetadata() = 0;
    /**
     * Changes metadata of a given track.
     */
    virtual void updateTrackMetadata() = 0;
    /**
     * Updates the track positino in the playlist.
     */
    virtual void updateTrackPlaylistPosition() = 0;
};



}  // namespace database


#endif  // _VPLAYER_LIBRARY_DB_H
