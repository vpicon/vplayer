/**
 * Track.h
 *
 * Module: player
 *
 * Defines Track class interface.
 *
 */

#ifndef _VPLAYER_TRACK_H
#define _VPLAYER_TRACK_H

#include <ostream>


namespace player {


/**
 * A potentially playable element by the player. May be obtained by an
 * element stored in the database.
 */
class Track {
    /**
     * Track class, separate from the database track class, to keep some 
     * separation of modules.
     */
public:
    Track() {}

    ~Track() {}
};



// TODO is a stub.
std::ostream& operator<<(std::ostream &os, const Track &tr) {
    os << "this track stub";
    return os;
}


}  // namespace player 


#endif  // _VPLAYER_SAMPLE_FORMAT_H
