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
#include "SampleFormat.h"


namespace player {



class Input {
public:
    // Virtual destructor in polymorphic base classes 
    virtual ~Input();

    /**
     * Given a position in a buffer (obtained by getWritePosition() from Buffer
     * class), it reads data from input as much as it fits in the write position.
     * The function returns the actual number of bytes written to the buffer.
     * The buffer then has to be mark as written the amount of bytes written.
     */
    virtual size_t read(Buffer::Position writePos) = 0;


    /**
     * Given a time position between 0 and the duration of the Input track, sets
     * the position of the input reading to that of the seconds.
     * If the given position is larger than the duration of the track, sets the 
     * position to end of input data.
     */
    virtual void seek(double seconds) = 0;

    /**
     * Says if reading of input reached end of file.
     */
    virtual bool reachedEOF() const = 0;

    /**
     * Gives sample specifications of input.
     */
    virtual SampleFormat getSampleFormat() const = 0;

    /**
     * Gets the duration of the audio stored in input object.
     */
    virtual double getDuration() const = 0;

    /**
     * Gets the metadata stored in the input file, if any.
     */
    virtual int getMetadata() const = 0;
};



}  // namespace player


#endif  // _VPLAYER_INPUT_H
