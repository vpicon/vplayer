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


namespace player {

WavInput::WavInput(const std::string& filename) {
    
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

// TODO: is a stub.
int WavInput::getSampleSpecs() const {
    return {};
}

double WavInput::getDuration() const {
    return 0;
}



}  // namespace player


