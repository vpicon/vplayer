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


#include "database/Track.h" 
#include <ostream>


using database::Track;


namespace player {


/**
 * A class to represent the sequence of tracks to be played by the player,
 * on the playlist (album) given, without the playing queue. 
 */
class Tracklist {
    /**
     * Invariant:
     *    _tracks is non-empty
     *    _tracks.begin() <= _startingPos, _currentPos < _tracks.end()
     */
public:
    // CLASS DEFINITIONS AND CONSTANTS
    enum class Sorting { none, random };

    // CONSTRUCTORS 
    Tracklist(const std::vector<Track> &tracks, 
              std::vector<Track>::iterator startPosition,  // starting position
              bool shuffle = false);

    /**
     * Returns wether there is another track in the Tracklist.
     */
    bool existsNextTrack() const;
    /**
     * Returns wether there is track a previously in the Tracklist.
     */
    bool existsPrevTrack() const;

    /**
     * Provided there is another track in the tracklist (can be checked 
     * with existsNextTrack(), gives a const reference to such next Track 
     * object.
     *
     * If no such track exists, undefined behavior occurs.
     */
    const Track& nextTrack();
    /**
     * Provided there is a previous track in the tracklist (can be checked 
     * with existsPrevTrack(), gives a const reference to such Track 
     * object.
     *
     * If no such track exists, undefined behavior occurs.
     */
    const Track& prevTrack();

private:
    std::vector<Track> _tracks;
    const std::vector<Track>::iterator _startingPos;
    bool _shuffle;
     
    std::vector<Track>::iterator _currentPos;
};



// TODO: is a stub.
std::ostream& operator<<(std::ostream &os, const Tracklist& tl) {
    os << "this tracklist stub";
    return os;
}



}  // namespace player 



#endif  // _VPLAYER_TRACKLIST_H
