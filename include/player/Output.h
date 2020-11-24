/**
 * Output.h
 *
 * Module: player
 *
 * Defines Output class interface.
 *
 */

#ifndef _VPLAYER_OUTPUT_H
#define _VPLAYER_OUTPUT_H


#include "Buffer.h"
#include "SampleFormat.h"


namespace player {



class Output {
public:
    // Virtual destructor in polymorphic base classes 
    virtual ~Output();

    // Virtual 


    /**
     * Given a position in a buffer (obtained by getReadPosition() from Buffer
     * class), it writes data to output as much as it fits in the output buffer, 
     * and there is available data in the buffer.
     * The function returns the actual number of bytes read from the buffer (and
     * written to output).
     */
    virtual size_t write(Buffer::Position readPos) = 0;

    /**
     * Gives sample specifications of input.
     */
    virtual int getSupportedFormats() const = 0;

    virtual void play() = 0;

    virtual void pause() = 0;
};



}  // namespace player


#endif  // _VPLAYER_OUTPUT_H
