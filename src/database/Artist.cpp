/**
 * Artist.cpp
 *
 * Module: database 
 *
 * Implements Artist empty destructors
 *
 */

#include "Artist.h"


namespace database {


Artist::Artist(int id, 
               std::string name, 
               std::string imgSource, 
               std::string bio)
    : _id{id},
      _name{name},
      _imgSource{imgSource},
      _bio{bio}
{
}


std::ostream& operator<<(std::ostream &os, const Artist &artist) {
    os << "Artist id: "   << artist.getId()
       << ", name: "      << artist.getName()
       << ", imgSource: " << artist.getImgSource()
       << ", bio: "       << artist.getBio();

    return os;
}



}  // namespace database
