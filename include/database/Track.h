/**
 * Track.h
 *
 * Module: database 
 *
 * Defines Track class interface.
 *
 */

#ifndef _VPLAYER_TRACK_H
#define _VPLAYER_TRACK_H


#include "Album.h"
#include "Artist.h"

#include <string>
#include <ostream>
#include <vector>


namespace database {



class Track {
public:
    Track(int id, 
          const std::string &title,
          const Album &album,
          const std::vector<Artist> &artists, 
          const std::string &dateOfAddition,   // TODO: Add format Date of addition to the library
          float duration,
          const std::string &source);

    Track(const std::string &title,
          const Album &album,
          const std::vector<Artist> &artists, 
          const std::string &dateOfAddition,   // TODO: Add format Date of addition to the library
          float duration,
          const std::string &source);

    // Minimal track constructor
    Track(const std::string &title);

    Track();

    // GETTERS
    int getId() const { return _id; }
    std::string getTitle() const { return _title; }
    Album getAlbum() const { return _album; }
    std::vector<Artist> getArtists() const { return _artists; }
    std::string getDate() const { return _date; }
    float getDuration() const { return _duration; }
    std::string getSource() const { return _source; }
    /**
     * Returns if the track has an album associated to it,
     * i.e a non-empty album with a non-empty title.
     */
    bool hasAlbum() const { return _album.getTitle() != ""; }

    // SETTERS
    void setId(int id) { _id = id; }
    void setTitle(const std::string &title) { _title = title; }
    void setAlbum(const Album &album) { _album = album; }
    void setArtists(const std::vector<Artist> &artists) { _artists = artists; }
    void setDate(const std::string &date) { _date = date; }
    void setDuration(const float duration) { _duration = duration; }
    void setSource(const std::string &source) { _source = source; }

    // MODIFYERS
    /**
     * Tries to add artist to the list of artists of the track, looking 
     * if it is not already there. Returns true if it could add the 
     * artist to the list (i.e. artist not there). False otherwise.
     */
    bool addArtist(const Artist &artist);
    /**
     * Tries to remove artist to the list of artists of the track, looking 
     * if it is there. Returns true if it could remove the artist from 
     * the list (i.e. artist not there). False otherwise.
     */
    bool removeArtist(const Artist &artist);
    /**
     * Tries to update artist from the list of artists of the track, looking 
     * if it is not already there (an artist with the same id, but other
     * attributes). Returns true if it could update the artist from the 
     * list (i.e. artist not there). False otherwise.
     */
    bool updateArtist(const Artist &artist);

private:
    int _id;
    std::string _title;
    Album _album;
    std::vector<Artist> _artists; 
    std::string _date;   // TODO: Add format Date of addition to the library
    float _duration;
    std::string _source;
};



inline bool operator==(const Track &lt, const Track &rt) {
    return lt.getId() == rt.getId()             &&
           lt.getTitle() == rt.getTitle()       &&
           lt.getAlbum() == rt.getAlbum()       &&
           lt.getArtists() == rt.getArtists()   &&
           lt.getDate() == rt.getDate()         &&
           lt.getDuration() == rt.getDuration() &&
           lt.getSource() == rt.getSource();
}

std::ostream& operator<<(std::ostream &os, const Track &tr);


}  // namespace database



#endif  // _VPLAYER_TRACK_H
