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
      _enc{enc}
{
}



SampleFormat::~SampleFormat()
{
}



int SampleFormat::calculateBitrate(const int frameRate, 
                                          const int bitDepth, 
                                          const int numChannels)
{
    return frameRate * bitDepth * numChannels;
}



int SampleFormat::getBitrate() const { 
    return SampleFormat::calculateBitrate(_frameRate, _bitDepth, _numChannels); 
}



std::ostream& operator<<(std::ostream &os, const SampleFormat &sf) {
    os << sf.getFrameRate() << " Hz, "
       << sf.getBitDepth() << "bit ";

    switch(sf.getEncoding()) {
        case SampleFormat::Encoding::signedEnc:
            os << "signed, ";
            break;
        case SampleFormat::Encoding::unsignedEnc:
            os << "unsigned, ";
            break;
        case SampleFormat::Encoding::floatEnc:
            os << "float, ";
            break;
    }
    
    if (sf.getNumChannels() == 1)
        os << "mono, ";
    else if (sf.getNumChannels() == 2)
        os << "stereo, ";
    else
        os << "other, ";

    os << (sf.getEndian() == SampleFormat::Endian::little ? "little endian" : "big endian");

    return os;
}




}  // namespace player 
