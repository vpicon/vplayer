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


#include <string>
#include <ostream>


namespace database {



class Album {
public:
    Album(int id = 0, 
          const std::string &title = "", 
          int year = 0,
          const std::string &imgSource = "");      

    // GETTERS
    int getId() const { return _id; }
    std::string getTitle() const { return _title; }
    int getYear() const { return _year; }
    std::string getImgSource() const { return _imgSource; }

    // SETTERS
    void setTitle(std::string title) { _title = title; }
    void setYear(int year) { _year = year; }
    void setImgSource(std::string source) { _imgSource = source; }

private:
    int _id;
    std::string _title;
    int _year;  
    std::string _imgSource;
};


std::ostream& operator<<(std::ostream &os, const Album &album);



}  // namespace database



#endif  // _VPLAYER_ALBUM_H
