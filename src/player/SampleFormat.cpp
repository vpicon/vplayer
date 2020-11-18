/**
 * SampleFormat.cpp
 *
 * Module: player
 *
 * Implements SampleFormat class.
 *
 */

#ifndef _VPLAYER_SAMPLE_FORMAT_H
#define _VPLAYER_SAMPLE_FORMAT_H


#include "SampleFormat.h"


namespace player {



SampleFormat::SampleFormat(int frameRate, 
                           int bitDepth,
                           int numChannels,
                           SampleFormat::Endiannes endian,
                           SampleFormat::Encoding end)
    : _frameRate{frameRate},
      _bitDepth{bitDepth},
      _numChannels{numChannels},
      _endian{endian},
      _enc{enc} {}


static inline int SampleFormat::calculateBitrate(int frameRate,
                                                 int bitDepth,
                                                 int numChannels) 
{
    return frameRate * bitDepth * numChannels;
}


inline int getBitrate() const { 
    return SampleFormat::calculateBitrate(_frameRate, _bitDepth, _numChannels); 
}



}  // namespace player 
