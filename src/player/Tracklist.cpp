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
                     Tracklist::Sorting sort)
    : _tracks{tracks},
      _startingPos{startPosition},
      _sort{sort},
      _playQueue{}
{
    _orderedTracks = orderTracks(_tracks, _startingPos, _sort);
}



Track Tracklist::getNextTrack() {
    return {};
}



std::vector<Track> Tracklist::orderTracks(const std::vector<Track> &tracks, 
                                          const std::vector<Track>::iterator startingPos,
                                          Tracklist::Sorting sort) 
{
    return {};
}








}  // namespace player
