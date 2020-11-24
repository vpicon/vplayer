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

extern "C" {
    #include <pulse/pulseaudio.h>
}



namespace player {



class PulseaudioOutput : public Output {
public:
    PulseaudioOutput(Buffer& buffer);

    ~PulseaudioOutput();


    void open(SampleFormat sf) override;

    void close() override;


    size_t write(Buffer::Position readPos) override;

    void drop() override;


    void pause() override;

    void unpause() override; 


    size_t outSpace() override;

private:
    Buffer& _buffer;

    /**
     * Given SampleFormat object, converts it to a pa_sample_format_t
     * type.
     */
    pa_sample_format_t toPulseSampleFormat(SampleFormat sf) const;

    /**
     * Given SampleFormat object returns a pa_sample_spec type 
     */
    pa_sample_spec toPulseSampleSpec(SampleFormat sf) const;
};



}  // namespace player


#endif  // _VPLAYER_PULSEAUDIO_OUTPUT_H
