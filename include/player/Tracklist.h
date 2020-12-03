/**
 * Tracklist.h
 *
 * Module: player
 *
 * Defines Tracklist class interface.
 *
 */

#ifndef _VPLAYER_TRACKLIST_H
#define _VPLAYER_TRACKLIST_H

#include <ostream>


namespace player {


/**
 * A class to represent the sequence of tracks to be played by the player,
 * by the playlist (album) given, and the playing queue. (Yes, the name
 * may not the most accurate, but it works.)
 */
class Tracklist {
public:
    Tracklist() {}

    ~Tracklist() {}

    Track *nextTrack() { return nullptr; }
};



// TODO: is a stub.
std::ostream& operator<<(std::ostream &os, const Tracklist& tl) {
    os << "this tracklist stub";
    return os;
}



}  // namespace player 



#endif  // _VPLAYER_TRACKLIST_H
