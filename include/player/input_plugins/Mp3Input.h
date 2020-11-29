/**
 * Mp3Input.h
 *
 * Module: player
 *
 * Defines Mp3Input class interface.
 *
 */

#ifndef _VPLAYER_MP3_INPUT_H
#define _VPLAYER_MP3_INPUT_H


#include "Input.h"
#include "Buffer.h"

#include <fstream>
#include <string>


namespace player {


/**
 * Reads and processes an mp3 file format, using the mpg123 mp3 library.
 */
class Mp3Input : public Input {
    /**
     * TODO: Class invariants
     */
public:
    /**
     * Constructs a new Input object, reading data into buffer.
     */
    Mp3Input(const std::string& filename);

    ~Mp3Input();

    /**
     * Given a position in a buffer (obtained by getWritePosition() from Buffer
     * class), reads as much data from wav file as it fits in the write position.
     * The function returns the actual number of bytes written to the buffer.
     */
    size_t read(Buffer::Position writePos) override;

    void seek(double seconds) override;

    bool reachedEOF() const override;

    SampleFormat getSampleFormat() const override { return _sampleFormat; }

    double getDuration() const override;

private:
    std::string _filename;

    SampleFormat _sampleFormat;

    size_t _dataSize;              // Number of bytes of PCM data

    bool _eof;
};



}  // namespace player


#endif  // _VPLAYER_MP3_INPUT_H
