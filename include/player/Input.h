/**
 * Input.h
 *
 * Module: player
 *
 * Defines Input class interface.
 *
 */

#ifndef _VPLAYER_INPUT_H
#define _VPLAYER_INPUT_H


#include "Buffer.h"


namespace player {



class Input {
public:
    /**
     * Given a position in a buffer (obtained by getWritePosition() from Buffer
     * class), it reads data from input as much as it fits in the write position.
     * The function returns the actual number of bytes written to the buffer.
     */
    virtual size_t read(Buffer::Position writePos) = 0;


    /**
     * Given a time position between 0 and the duration of the Input track, sets
     * the position of the input reading to that of the seconds.
     */
    virtual void seek(double seconds) = 0;

    /**
     * Says if reading of input reached end of file.
     */
    virtual bool reachedEOF() = 0;

    /**
     * Gives sample specifications of input.
     */
    virtual SampleSpecs getSampleSpecs() = 0;
};



}  // namespace player


#endif  // _VPLAYER_INPUT_H
