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

    /**
     * Opens a new output connection to a sink, to send data to.
     */
    virtual void open() = 0;

    /**
     * Closes an opened output connection to a sink.
     */
    virtual void close() = 0;

    /**
     * Given a position in a buffer (obtained by getReadPosition() from Buffer
     * class), it writes data to output as much as it fits in the output buffer, 
     * and there is available data in the buffer.
     * The function returns the actual number of bytes read from the buffer (and
     * written to output).
     */
    virtual size_t write(Buffer::Position readPos) = 0;

    /**
     * Drops all data stored in output buffers.
     */
    virtual void drop() = 0;

    /**
     * Pauses the playback of data in output.
     */
    virtual void pause() = 0;

    /**
     * Resumes the playback of data in output.
     */
    virtual void unpause() = 0;

    /**
     * Gives amount of space available in the buffers at the output side.
     */
    virtual size_t outSpace() = 0;
};



}  // namespace player


#endif  // _VPLAYER_OUTPUT_H
