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


#include <string>
#include <ostream>


namespace database {



class Track {
public:
    Track(int id = 0, 
          const std::string &title = "", 
          // const std::string &albumId = "", 
          const std::string &dateOfAddition = "",
          const std::string &source = "");      

    // GETTERS
    // int getId() const { return _id; }
    // std::string getName() const { return _name; }
    // std::string getImgSource() const { return _imgSource; }
    // std::string getBio() const { return _bio; }

    // SETTERS
    // void setName(std::string name) { _name = name; }
    // void setImgSource(std::string source) { _imgSource = source; }
    // void setBio(std::string bio) { _bio = bio; }

private:
    int _id;
    std::string _title;
    std::string _date;   // Date of addition to the library
    std::string _source;
};


std::ostream& operator<<(std::ostream &os, const Track &tr);


}  // namespace database



#endif  // _VPLAYER_TRACK_H
