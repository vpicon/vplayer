/**
 * WavInput.h
 *
 * Module: player
 *
 * Defines WavInput class interface.
 *
 */

#ifndef _VPLAYER_WAV_INPUT_H
#define _VPLAYER_WAV_INPUT_H


#include "Input.h"
#include "Buffer.h"

#include <string>


namespace player {


/**
 * Reads and processes a Wav file format, implementing the Input interface.
 *
 * The WAV file format is registered at RFC 2361. An overview explanation of 
 * the format is given at: 
 * http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */
class WavInput : public Input {
public:
    WavInput(const std::string& filename);

    /**
     * Given a position in a buffer (obtained by getWritePosition() from Buffer
     * class), it reads data from input as much as it fits in the write position.
     * The function returns the actual number of bytes written to the buffer.
     */
    size_t read(Buffer::Position writePos) override;

    /**
     * Given a time position between 0 and the duration of the Input track, sets
     * the position of the input reading to that of the seconds.
     */
    void seek(double seconds) override;

    /**
     * Says if reading of input reached end of file.
     */
    bool reachedEOF() const override;

    /**
     * Gives sample specifications of input.
     * TODO: Create a Class suporting Sample Specifications, and
     * use it as return type.
     */
    int getSampleSpecs() const override;

    /**
     * Gets the duration of the wav audio stored in this WavInput object.
     */
    double getDuration() const override;
};



}  // namespace player


#endif  // _VPLAYER_WAV_INPUT_H
