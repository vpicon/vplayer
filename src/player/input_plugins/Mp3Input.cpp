/**
 * Mp3Input.cpp
 *
 * Module: player
 *
 * Implements Mp3Input class interface.
 *
 */

#include "input_plugins/Mp3Input.h"
#include "SampleFormat.h"
#include "Buffer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>


namespace player {


// TODO: change order buffer filename
// TODO: define specific error types
// TODO: is a stub
Mp3Input::Mp3Input(const std::string& filename)
    : _filename{filename}
{
}



// TODO: is a stub
Mp3Input::~Mp3Input()
{
}



// TODO: is a stub
size_t Mp3Input::read(Buffer::Position writePos) {
    return 0;
}



// TODO: is a stub
void Mp3Input::seek(double seconds) {
}



// TODO: is a stub
bool Mp3Input::reachedEOF() const {
    return _eof;
}



// TODO: is a stub
double Mp3Input::getDuration() const {
    return 0.0;
}

}  // namespace player
