/**
 * WavInput.cpp
 *
 * Module: player
 *
 * Implements WavInput class interface.
 *
 */

#include "input_plugins/WavInput.h"
#include "Buffer.h"

#include <string>
#include <fstream>
#include <iostream>


namespace player {



WavInput::WavInput(const std::string& filename)
    : _filename{filename},
      _file{filename, std::ios_base::binary | std::ios_base::in}
{
    if (!_file) {
        // TODO: define specific error types
        throw std::runtime_error("Could not open file: " + filename);  
    }

    if ( !(readRIFFChunk() && readFormatChunk() && readDataChunkHeader()) ) {
        // TODO: define specific error types
        throw std::runtime_error("Could not read WAV format");
    }
}



// TODO: is a stub.
size_t WavInput::read(Buffer::Position writePos) {
    return writePos.size();
}



// TODO: is a stub.
void WavInput::seek(double seconds) {
    seconds = 0;
}



// TODO: is a stub.
bool WavInput::reachedEOF() const {
    return false;
}



double WavInput::getDuration() const {
    return 0;
}



bool WavInput::readRIFFChunk() {
    char buf[4];

    // Read RIFF
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "RIFF")
        return false;

    // Read int
    uint32_t size;
    _file.read(reinterpret_cast<char *>(&size), 4);
    if (!_file)
        return false;
    size += 8;


    // Read WAVE
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "WAVE")
        return false;

    // RIFF Header Chunk read successfully
    return true;
}



// TODO: is a stub
bool WavInput::readFormatChunk() {
    return false;
}



bool WavInput::readDataChunkHeader() {
    char buf[4];

    // Read RIFF
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "data")
        return false;

    // Read int
    uint32_t size;
    _file.read(reinterpret_cast<char *>(&size), 4);
    if (!_file)
        return false;
    _dataSize = size;

    return true;
}



}  // namespace player
