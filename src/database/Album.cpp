/**
 * Album.cpp
 *
 * Module: database 
 *
 * Implements Album class
 *
 */

#include "Album.h"


namespace database {


Album::Album(int id, 
             const std::string &title, 
             int year,
             const std::string &imgSource)   
    : _id{id},
      _title{title},
      _year{year},
      _imgSource{imgSource}
{
}


std::ostream& operator<<(std::ostream &os, const Album &album) {
    os << "Album id: "    << album.getId()
       << ", title: "     << album.getTitle()
       << ", year: "      << album.getYear()
       << ", imgSource: " << album.getImgSource();

    return os;
}



}  // namespace database
