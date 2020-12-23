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
 * by the playlist (album) given, and the playing queue. (Yes, the name
 * may not the most accurate, but it works.)
 */
class Tracklist {
public:
    // CLASS DEFINITIONS AND CONSTANTS
    enum class Sorting { native, title, artist, album, shuffle };

    // CONSTRUCTORS 
    Tracklist(const std::vector<Track> &tracks, 
              std::vector<Track>::iterator startPosition,  // starting position
              Sorting sort = Sorting::native);

    /**
     * Gives a pointer to the next Track in the tracklist, or null if there 
     * is no next track to play.
     */
    Track getNextTrack();

private:
    std::vector<Track> _tracks;
    const std::vector<Track>::iterator _startingPos;

    Sorting _sort;
    std::vector<Track> _orderedTracks;
    std::vector<Track>::iterator _currentPos;

    std::vector<Track> _playQueue;


    // HELPTER METHODS
    std::vector<Track> orderTracks(const std::vector<Track> &tracks, 
                                   const std::vector<Track>::iterator startingPos,
                                   Tracklist::Sorting sort);
                                   
};



// TODO: is a stub.
std::ostream& operator<<(std::ostream &os, const Tracklist& tl) {
    os << "this tracklist stub";
    return os;
}



}  // namespace player 



#endif  // _VPLAYER_TRACKLIST_H
