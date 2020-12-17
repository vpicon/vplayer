/**
 * Playlist.cpp
 *
 * Module: database 
 *
 * Implements Playlist empty destructors
 *
 */

#include "Playlist.h"


namespace database {


Playlist::Playlist(int id, 
                   std::string name, 
                   std::string imgSource, 
                   std::vector<Track> tracks)
    : _id{id},
      _name{name},
      _imgSource{imgSource},
      _tracks{tracks}
{
}



Playlist::Playlist(std::string name, 
                   std::string imgSource, 
                   std::vector<Track> tracks)
    : Playlist(0, name, imgSource, tracks)
{
}



Playlist::Playlist()
    : Playlist(0, "", "", {})
{
}



void Playlist::addTrack(const Track &track, int position) {
    _tracks.insert(_tracks.begin() + position, track);
}


/*
bool Playlist::removeTrack(const Track &track) {
    int givenId = track.getId();

    // Find the position of the given artist in the list
    size_t position = 0;  
    for (const auto &otherTrack : _tracks) {
        if (otherTrack.getId() == givenId) {
            break;
        }
        position++;
    }

    // Check if the artist was found
    bool found = position < _tracks.size();

    // Remove artist from list (if found)
    if (found) {
        _tracks.erase(_tracks.begin() + position);
    }

    return found;
}



bool Playlist::updateTrack(const Track &track) {
    int givenId {track.getId()};

    bool found = false;
    for (auto &otherTrack : _tracks) {
        if (otherTrack.getId() == givenId) {
            found = true;
            otherTrack = track;
            break;
        }
    }

    return found;
}
*/



std::ostream& operator<<(std::ostream &os, const Playlist &playlist) {
    os << "Playlist " << playlist.getName() << ": ";

    for (const Track &track : playlist.getTracks()) 
        os << "\t" << track << "\n";

    return os;
}



}  // namespace database
