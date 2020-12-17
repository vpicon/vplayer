/**
 * Playlist.h
 *
 * Module: database 
 *
 * Defines Playlist class interface.
 *
 */

#ifndef _VPLAYER_PLAYLIST_H
#define _VPLAYER_PLAYLIST_H


#include "Track.h"

#include <string>
#include <ostream>
#include <vector>


namespace database {



class Playlist {
public:
    Playlist(int id, 
             std::string name, 
             std::string imgSource, 
             std::vector<Track> tracks);      

    Playlist(std::string name, 
             std::string imgSource, 
             std::vector<Track> tracks);      

    Playlist();

    // GETTERS
    int getId() const { return _id; }
    std::string getName() const { return _name; }
    std::string getImgSource() const { return _imgSource; }
    std::vector<Track> getTracks() const { return _tracks; }
    int numTracks() const { return _tracks.size(); }

    // SETTERS
    void setId(int id) { _id = id; }
    void setName(std::string name) { _name = name; }
    void setImgSource(std::string source) { _imgSource = source; }
    void setTracks(const std::vector<Track> &tracks) { _tracks = tracks; }

    // MODIFYERS
    /**
     * Adds track to the list of tracks of this playlist objects. The 
     * track is added before the element ordered by the given position,
     * where 0 <= position <= numTracks.
     *
     * That is, if position is 0, the element is stored at the beginning
     * of the list, moving all elements one position further. If position
     * is numTracks, then the element is positioned at the end of the 
     * list.
     */
    void addTrack(const Track &track, int position);
    /**
     * Tries to remove track to the list of tracks of the track, looking 
     * if it is there. Returns true if it could remove the track from 
     * the list (i.e. track not there). False otherwise.
     */
    // bool removeTrack(const Track &track);
    /**
     * Tries to update all appearances of the given track from the list 
     * of tracks of the track. Returns true if it could update the 
     * track from the list, false otherwise.
     */
    // bool updateTrack(const Track &track);

private:
    int _id;
    std::string _name;
    std::string _imgSource;
    std::vector<Track> _tracks;
};


std::ostream& operator<<(std::ostream &os, const Playlist &playlist);


}  // namespace database



#endif  // _VPLAYER_PLAYLIST_H
