/**
 * PulseaudioOutput.cpp
 *
 * Module: player
 *
 * Implements WavInput class interface.
 *
 */

#include "output_plugins/PulseaudioOutput.h"
#include "output_plugins/Pulse.h"
#include "Buffer.h"



namespace player {

    

// TODO: define specific error types
PulseaudioOutput::PulseaudioOutput(Buffer& buffer)
    : _buffer{buffer}
{
    if (pulse_init() != 0) {
        std::runtime_error("Could not initialize pulseaudio.");
    }
}



PulseaudioOutput::~PulseaudioOutput()
{
    if (pulse_exit() != 0) {
        std::runtime_error("Could not exit pulseaudio.");
    }
}



// TODO: is a stub
void PulseaudioOutput::open() {
    return;
}



// TODO: is a stub
void PulseaudioOutput::close() {
    return;
}



// TODO: is a stub
size_t PulseaudioOutput::write(Buffer::Position readPos) {
    return 0;
}



// TODO: is a stub
void PulseaudioOutput::drop() {
    return;
}



// TODO: is a stub
void PulseaudioOutput::pause() {
    return;
}



// TODO: is a stub
void PulseaudioOutput::unpause() {
    return;
}



// TODO: is a stub
size_t PulseaudioOutput::outSpace() {
    return 0;
}






}  // namespace player
