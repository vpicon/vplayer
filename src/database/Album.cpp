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
             const Artist &artist,
             int year,
             const std::string &imgSource)   
    : _id{id},
      _title{title},
      _artist{artist},
      _year{year},
      _imgSource{imgSource}
{
}



Album::Album(const std::string &title, 
             const Artist &artist,
             int year,
             const std::string &imgSource)   
    : Album(0, title, artist, year, imgSource)
{
}



Album::Album(const std::string &title, 
             const Artist &artist)
    : Album(0, title, artist, 0, "")
{
}



Album::Album()
    : Album(0, "", Artist{}, 0, "")
{
}



std::ostream& operator<<(std::ostream &os, const Album &album) {
    os << "Album id: "    << album.getId()
       << ", title: "     << album.getTitle()
       << ", artist: {"   << album.getArtist() << "}"
       << ", year: "      << album.getYear()
       << ", imgSource: " << album.getImgSource();

    return os;
}



}  // namespace database
