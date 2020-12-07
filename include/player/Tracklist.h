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
    // CLASS DEFINITIONS AND CONSTANTS
    enum class Sorting { native, title, artist, album, shuffle };

    // CONSTRUCTORS 
    Tracklist(/* std::vector<Track> tracks, */ Sorting sort): _sort{sort} {}

    ~Tracklist() {}


    /**
     * Gives a pointer to the next Track in the tracklist, or null if there 
     * is no next track to play.
     */
    const void *getNextTrack() { return nullptr; }

private:
    // std::vector<Track> _tracks;
    
    Sorting _sort;
};



// TODO: is a stub.
std::ostream& operator<<(std::ostream &os, const Tracklist& tl) {
    os << "this tracklist stub";
    return os;
}



}  // namespace player 



#endif  // _VPLAYER_TRACKLIST_H
