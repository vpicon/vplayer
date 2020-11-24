/**
 * PulseaudioOutput.cpp
 *
 * Module: player
 *
 * Implements WavInput class interface.
 *
 */

#include "output_plugins/PulseaudioOutput.h"
#include "Buffer.h"



namespace player {

    

// TODO: define specific error types
PulseaudioOutput::PulseaudioOutput(Buffer& buffer)
    : _buffer{buffer}
{
}



PulseaudioOutput::~PulseaudioOutput()
{
}


// TODO: is a stub
size_t PulseaudioOutput::write(Buffer::Position readPos) {
    return 0;
}



int PulseaudioOutput::getSupportedFormats() const {
    return 0;
}




}  // namespace player
