/**
 * Artist.h
 *
 * Module: database 
 *
 * Defines Artist class interface.
 *
 */

#ifndef _VPLAYER_ARTIST_H
#define _VPLAYER_ARTIST_H


#include <string>
#include <ostream>


namespace database {



class Artist {
public:
    // CONSTRUCTORS
    Artist(int id, 
           std::string name, 
           std::string imgSource, 
           std::string bio);      

    Artist(std::string name, 
           std::string imgSource, 
           std::string bio);      

    // Minimal artist constructor
    Artist(std::string name);

    Artist();

    // GETTERS
    int getId() const { return _id; }
    std::string getName() const { return _name; }
    std::string getImgSource() const { return _imgSource; }
    std::string getBio() const { return _bio; }

    // SETTERS
    void setId(int id) { _id = id; }
    void setName(std::string name) { _name = name; }
    void setImgSource(std::string source) { _imgSource = source; }
    void setBio(std::string bio) { _bio = bio; }

private:
    int _id;
    std::string _name;
    std::string _imgSource;
    std::string _bio;
};



inline bool operator==(const Artist &la, const Artist &ra) {
    return la.getId() == ra.getId()               &&
           la.getName() == ra.getName()           &&
           la.getImgSource() == ra.getImgSource() &&
           la.getBio() == ra.getBio();
}

std::ostream& operator<<(std::ostream &os, const Artist &artist);



}  // namespace database



#endif  // _VPLAYER_ARTIST_H
