/**
 * Album.h
 *
 * Module: database 
 *
 * Defines Album class interface.
 *
 */

#ifndef _VPLAYER_ALBUM_H
#define _VPLAYER_ALBUM_H


#include "Artist.h"

#include <string>
#include <ostream>


namespace database {



class Album {
public:
    // CONSTRUCTORS
    Album(int id, 
          const std::string &title, 
          const Artist &artist,
          int year,
          const std::string &imgSource);      
    
    Album(const std::string &title, 
          const Artist &artist,
          int year,
          const std::string &imgSource);      

    // Album minimal constructor
    Album(const std::string &title, 
          const Artist &artist);

    Album();      


    // GETTERS
    int getId() const { return _id; }
    std::string getTitle() const { return _title; }
    Artist getArtist() const { return _artist; }
    int getYear() const { return _year; }
    std::string getImgSource() const { return _imgSource; }

    // SETTERS
    void setId(int id) { _id = id; }
    void setTitle(const std::string &title) { _title = title; }
    void setArtist(const Artist &artist) { _artist = artist; }
    void setYear(int year) { _year = year; }
    void setImgSource(const std::string &source) { _imgSource = source; }

private:
    int _id;
    std::string _title;
    Artist _artist;
    int _year;  
    std::string _imgSource;
};


std::ostream& operator<<(std::ostream &os, const Album &album);



}  // namespace database



#endif  // _VPLAYER_ALBUM_H
