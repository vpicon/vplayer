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

#include <vector>


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
     *
     * The albums and artists are added to the database (if not already
     * there), and its id is set to the given by the database. The 
     * track id is also set to the one in the database.
     *
     * Returns false on any error or failure, true otherwise.
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
     * database, links the track to the playlist, setting it to the 
     * given position in the playlist.
     *
     * The position satisfies 0 <= pos <= playlist.numTracks(); being 
     * the last equality the case where we add the track to the end of 
     * the list.
     *
     * The playlist object must be liable to the database, that is, 
     * all its tracks must be linked to the playlist in the database.
     *
     * When adding the track to the database, its id is set to the
     * id given by the database. And the track is added to given position
     * in the list of tracks in the given playlist object.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool addTrackToPlaylist(Track &track, Playlist &playlist, int pos) = 0;

    // GETTERS
    /**
     * Gives all the tracks in the library.
     */
    virtual std::vector<Track> getAllTracks() = 0;
    /**
     * Get the track with the given id number.
     */
    virtual Track getTrack(const int id) = 0;
    /**
     * Gives all the playlists in the library. Their names and id,
     * but not the contents of each of the playlists.
     */
    virtual std::vector<Playlist> getAllPlaylists() = 0;
    /**
     * Gives all the tracks in a given playlist.
     */
    virtual void getPlaylistTracks() = 0;
    /**
     * Gives all the albums in the database.
     */
    virtual std::vector<Album> getAllAlbums() = 0;
    /**
     * Given an album previously stored in the database, gives all the 
     * tracks of such album.
     */
    virtual std::vector<Track> getAlbumTracks(const Album &album) = 0;
    /**
     * Gives all the artists in the database.
     */
    virtual std::vector<Artist> getAllArtists() = 0;
    /**
     * Given an artist previously stored in the database, gives all the 
     * albums of such given artist.
     */
    virtual std::vector<Album> getArtistAlbums(const Artist &artist) = 0;

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
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool updateAlbum(Album &album) = 0;
    /**
     * Updates the artist stored in the database with the same id as 
     * the @artist id. 
     *
     * Returns false on any error or failure, true otherwise.
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

    // DELETERS
    /**
     * Given a track object, previously added to the database, removes
     * it from the database, and removing if necessary all associated 
     * objects with it: artists and albums, and references to playlists.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool deleteTrack(const Track &track) = 0; 
    /**
     * Removes the entire playlist, with all the song references in it. But the 
     * songs still remain in the library.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool deletePlaylist() = 0; 
    /**
     * Given a playlist object, previously added to the database, and
     * a position (0 <= pos < numTracks); deletes the link between the
     * playlist and the track at the given position, also removing
     * such track from the given playlist object tracks list.
     *
     * Returns false on any error or failure, true otherwise.
     */
    virtual bool removeTrackFromPlaylist(Playlist &playlist, int pos) = 0; 
};



}  // namespace database


#endif  // _VPLAYER_LIBRARY_DB_H
