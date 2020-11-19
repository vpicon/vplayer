/**
 * SampleFormat.cpp
 *
 * Module: player
 *
 * Implements SampleFormat class.
 *
 */

#include "SampleFormat.h"


namespace player {


SampleFormat::SampleFormat(int frameRate, 
                           int bitDepth,
                           int numChannels,
                           SampleFormat::Endian endian,
                           SampleFormat::Encoding enc)
    : _frameRate{frameRate},
      _bitDepth{bitDepth},
      _numChannels{numChannels},
      _endian{endian},
      _enc{enc} {}


inline int SampleFormat::calculateBitrate(int frameRate,
                                          int bitDepth,
                                          int numChannels) 
{
    return frameRate * bitDepth * numChannels;
}


inline int SampleFormat::getBitrate() const { 
    return SampleFormat::calculateBitrate(_frameRate, _bitDepth, _numChannels); 
}



}  // namespace player 
