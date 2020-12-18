/**
 * Track.cpp
 *
 * Module: database 
 *
 * Implements Track empty destructors
 *
 */

#include "Track.h"


namespace database {



Track::Track(int id, 
             const std::string &title,
             const Album &album,
             const std::vector<Artist> &artists, 
             const std::string &dateOfAddition,   // TODO: Add format Date of addition to the library
             float duration,
             const std::string &source)
    : _id{id},
      _title{title},
      _album{album},
      _artists{artists},
      _date{dateOfAddition},
      _duration{duration},
      _source{source}
{
}



Track::Track(const std::string &title,
             const Album &album,
             const std::vector<Artist> &artists, 
             const std::string &dateOfAddition,   // TODO: Add format Date of addition to the library
             float duration,
             const std::string &source)
    : Track(0, title, album, artists, dateOfAddition, duration, source)
{
}



Track::Track(const std::string &title)
    : Track(0, title, {}, {}, "", 0.0, "")
{
}



Track::Track()
    : Track(0, "", Album {}, std::vector<Artist> {}, "", 0.0, "")
{
}



bool Track::addArtist(const Artist &artist) {
    int givenId {artist.getId()};

    // Check if artist is already in list of artists
    bool found = false;
    for (auto trackArtist : _artists) {
        if (trackArtist.getId() == givenId) {
            found = true;
            break;
        }
    }

    // Add artist to the list
    if (!found)
        _artists.push_back(artist);

    return !found;
}



bool Track::removeArtist(const Artist &artist) {
    int givenId = artist.getId();

    // Find the position of the given artist in the list
    size_t position = 0;  
    for (auto trackArtist : _artists) {
        if (trackArtist.getId() == givenId) {
            break;
        }
        position++;
    }

    // Check if the artist was found
    bool found = position < _artists.size();

    // Remove artist from list (if found)
    if (found) {
        _artists.erase(_artists.begin() + position);
    }

    return found;
}



bool Track::updateArtist(const Artist &artist) {
    int givenId {artist.getId()};

    bool found = false;
    for (auto &trackArtist : _artists) {
        if (trackArtist.getId() == givenId) {
            found = true;
            trackArtist = artist;
            break;
        }
    }

    return found;
}



std::ostream& operator<<(std::ostream &os, const Track &track) {
    os << "Track id: " << track.getId()
       << ", title: "  << track.getTitle();

    return os;
}



}  // namespace database
