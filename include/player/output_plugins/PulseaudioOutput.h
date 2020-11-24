/**
 * PulseaudioOutput.h
 *
 * Module: player
 *
 * Defines PulseaudioOutput class interface.
 *
 */

#ifndef _VPLAYER_PULSEAUDIO_OUTPUT_H
#define _VPLAYER_PULSEAUDIO_OUTPUT_H


#include "Output.h"
#include "Buffer.h"



namespace player {



class PulseaudioOutput : public Output {
public:
    PulseaudioOutput(Buffer& buffer);

    ~PulseaudioOutput();

    size_t write(Buffer::Position readPos) override;


    int getSupportedFormats const override;
private:
    Buffer& _buffer;
};



}  // namespace player


#endif  // _VPLAYER_PULSEAUDIO_OUTPUT_H
