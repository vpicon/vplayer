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


#include "Track.h"
#include "Album.h"
#include "Artist.h"
#include "Playlist.h"



namespace database {



class LibraryDB {
public:
    // Virtual destructor in polymorphic base classes 
    virtual ~LibraryDB();

    // INSERTERS
    /**
     * Adds a new track to the library. Returns false on any failure,
     * true otherwise.
     *
     * No checks are made wether there is a track with same artists,
     * title, source, nor any field.
     */
    virtual bool insertNewTrack(Track &track) = 0;
    /**
     * Inserts new playlist to the database, given there is no playlist
     * with the given name already stored in the database.
     *
     * The playlist must have no tracks associated with it (must be empty).
     *
     * The given playslist object is modified to store the id given by the
     * database.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool insertNewPlaylist(Playlist &playlist) = 0;
    /**
     * Given a track and playlist, both previously added to the 
     * database, links the track to the playlist.
     *
     * The playlist object must be liable to the database, that is, 
     * all its tracks must be linked to the playlist in the database.
     *
     * When adding the track to the database, its id is set to the
     * id given by the database. And the track is added to the list 
     * of tracks in the given playlist object.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool addTrackToPlaylist(Track &track, Playlist &playlist) = 0;

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
     * Gives all the playlists in the library. Their names and id,
     * but not the contents of each of the playlists.
     */
    virtual void getPlaylists() = 0;
    /**
     * Gives all the tracks in a given album.
     */
    virtual void getAlbumTracks() = 0;
    /**
     * Get the track with the given id number.
     */
    virtual Track getTrack(const int id) = 0;
    /**
     * Gives all the tracks of a given author.
     */
    virtual void getArtistAlbums() = 0;

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
     * Updates the album stored in the database with the same id as 
     * the @album id. 
     *
     * Returns true on success. False otherwise on any errors.
     */
    virtual bool updateAlbum(Album &album) = 0;
    /**
     * Updates the artist stored in the database with the same id as 
     * the @artist id. 
     *
     * Returns true on success. False otherwise on any errors.
     */
    virtual bool updateArtist(Artist &artist) = 0;
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
