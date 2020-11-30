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
#include "SampleFormat.h"

extern "C" {
    #include <pulse/pulseaudio.h>
}



namespace player {

    

// TODO: define specific error types
PulseaudioOutput::PulseaudioOutput() {
    if (pulse_init() != 0) {
        std::runtime_error("Could not initialize pulseaudio.");
    }
}



PulseaudioOutput::~PulseaudioOutput() {
    // Close any output connections (if any)
    pulse_close();

    // Exit pulseaudio output plugin
    if (pulse_exit() != 0) {
        std::runtime_error("Could not exit pulseaudio.");
    }
}



void PulseaudioOutput::open(SampleFormat sf) {
    pa_sample_spec ss = toPulseSampleSpec(sf);
    int rc = pulse_open(ss);
    if (rc != 0) {
        std::runtime_error("error opening");
    }
}



void PulseaudioOutput::close() {
    pulse_close();
}



size_t PulseaudioOutput::write(Buffer::Position readPos) {
    if (readPos.toPointer() == nullptr || readPos.size() == 0)
        return 0;
    return pulse_write(readPos.toPointer(), readPos.size());
}



void PulseaudioOutput::drop() {
    pulse_drop();
}



void PulseaudioOutput::pause() {
    pulse_pause();
}



void PulseaudioOutput::unpause() {
    pulse_unpause();
}



size_t PulseaudioOutput::outSpace() {
    return pulse_buffer_space();
}



pa_sample_format_t PulseaudioOutput::toPulseSampleFormat(const SampleFormat& sf) const {
    SampleFormat::Encoding enc = sf.getEncoding();
    bool isBigEndian = sf.getEndian() == SampleFormat::Endian::big;
    int bitDepth = sf.getBitDepth();

    if (enc == SampleFormat::Encoding::unsignedEnc && bitDepth == 8)
        return PA_SAMPLE_U8;

    if (enc == SampleFormat::Encoding::signedEnc) {
		if (bitDepth == 16)
			return isBigEndian ? PA_SAMPLE_S16BE : PA_SAMPLE_S16LE;
		if (bitDepth == 24)
			return isBigEndian ? PA_SAMPLE_S24BE : PA_SAMPLE_S24LE;
		if (bitDepth == 32)
			return isBigEndian ? PA_SAMPLE_S32BE : PA_SAMPLE_S32LE;
    }

    return PA_SAMPLE_INVALID;   
}



pa_sample_spec PulseaudioOutput::toPulseSampleSpec(const SampleFormat& sf) const {
    pa_sample_spec ss;

    ss.format   = toPulseSampleFormat(sf);
    ss.rate     = sf.getFrameRate();
    ss.channels = sf.getNumChannels();

    return ss;
}




}  // namespace player
