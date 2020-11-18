/**
 * SampleFormat.h
 *
 * Module: player
 *
 * Defines SampleFormat class interface.
 *
 */

#ifndef _VPLAYER_SAMPLE_FORMAT_H
#define _VPLAYER_SAMPLE_FORMAT_H


#include "SampleFormat.h"


namespace player {


/**
 * A class to represent the format of a some PCM data. 
 */
class SampleFormat {
public:
    enum class Endiannes { littleEndian, bigEndian };
    enum class Encoding { signedEnc, unsignedEnc, floatEnc };

    // CONSTRUCTORS AND DESTRUCTORS
    /**
     * Constructs a new SampleFormat object, where frameRate is number of 
     * samples per second, bit depth is number of bits to represent a single
     * sample, numChannels the number of channels of each frame. endian and
     * enc refer to the data encoding of the PCM data.
     */
    SampleFormat(int frameRate, 
                 int bitDepth, 
                 int numChannels, 
                 Endiannes endian, 
                 Encoding enc);

    ~SampleFormat() {}


    // CLASS CONSTANTS AND METHODS

    static inline int calculateBitrate(int frameRate, 
                                       int bitDepth, 
                                       int numChannels);

    // ACCESSORS
    inline int getBitrate() const;

private:
    int _frameRate;
    int _bitDepth; 
    int _numChannels;
    // int _channelMask; // Not supported 
    Endiannes _endian;
    Encoding  _enc;
};



}  // namespace player 


#endif  // _VPLAYER_SAMPLE_FORMAT_H
