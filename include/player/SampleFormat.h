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

#include <ostream>


namespace player {


/**
 * A class to represent the format of a some PCM data. 
 */
class SampleFormat {
public:
    enum class Endian { little, big };
    enum class Encoding { signedEnc, unsignedEnc, floatEnc };

    // CONSTRUCTORS AND DESTRUCTORS
    /**
     * Constructs a new SampleFormat object, where frameRate is number of 
     * samples per second, bit depth is number of bits to represent a single
     * sample, numChannels the number of channels of each frame. endian and
     * enc refer to the data encoding of the PCM data.
     */
    SampleFormat(int frameRate = 0, 
                 int bitDepth = 0, 
                 int numChannels = 0, 
                 Endian endian = Endian::little, 
                 Encoding enc = Encoding::signedEnc);

    ~SampleFormat();


    // CLASS CONSTANTS AND METHODS

    static int calculateBitrate(const int frameRate, 
                                       const int bitDepth, 
                                       const int numChannels);

    // ACCESSORS
    inline int getFrameRate() const { return _frameRate; }

    inline int getBitDepth() const { return _bitDepth; }

    inline int getNumChannels() const { return _numChannels; }
    
    inline Endian getEndian() const { return _endian; }

    inline Encoding getEncoding() const { return _enc; }
    
    int getBitrate() const;

private:
    int _frameRate;
    int _bitDepth; 
    int _numChannels;
    // int _channelMask; // Not supported 
    Endian _endian;
    Encoding  _enc;
};


std::ostream& operator<<(std::ostream &os, const SampleFormat &sf); 


}  // namespace player 


#endif  // _VPLAYER_SAMPLE_FORMAT_H
