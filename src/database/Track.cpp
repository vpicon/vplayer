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
               const std::string &dateOfAddition,
               const std::string &source)
    : _id{id},
      _title{title},
      _date{dateOfAddition},
      _source{source}
{
}


std::ostream& operator<<(std::ostream &os, const Track &tr) {
    os << "Track.";

    return os;
}



}  // namespace database
