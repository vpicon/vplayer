/**
 * Tracklist.cpp
 *
 * Module: player
 *
 * Implementation of the Tracklist class.
 *
 */


#include "Tracklist.h"



namespace player {



Tracklist::Tracklist(const std::vector<Track> &tracks, 
                     std::vector<Track>::iterator startPosition,
                     bool shuffle)
    : _tracks{tracks},
      _startingPos{startPosition},
      _shuffle{shuffle},
      _currentPos{startPosition}
{
}


// TODO: is a stub
bool Tracklist::existsNextTrack() const {
    return false;
}


// TODO: is a stub
bool Tracklist::existsPrevTrack() const {
    return false;
}


// TODO: is a stub
const Track& Tracklist::nextTrack() {
    return *_startingPos;
}


// TODO: is a stub
const Track& Tracklist::prevTrack() {
    return *_startingPos;
}



}  // namespace player
