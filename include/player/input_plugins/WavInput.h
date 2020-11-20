/**
 * WavInput.h
 *
 * Module: player
 *
 * Defines WavInput class interface.
 *
 */

#ifndef _VPLAYER_WAV_INPUT_H
#define _VPLAYER_WAV_INPUT_H


#include "Input.h"
#include "Buffer.h"

#include <fstream>
#include <string>


namespace player {


/**
 * Reads and processes a Wav file format, implementing the Input interface.
 *
 * The WAV file format is registered at RFC 2361. An overview explanation of 
 * the format is given at: 
 * http://www-mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html
 */
class WavInput : public Input {
    /**
     * TODO: Class invariants
     */
public:
    WavInput(const std::string& filename);

    ~WavInput() {}

    /**
     * Given a position in a buffer (obtained by getWritePosition() from Buffer
     * class), it reads data from input as much as it fits in the write position.
     * The function returns the actual number of bytes written to the buffer.
     */
    size_t read(Buffer::Position writePos) override;

    /**
     * Given a time position between 0 and the duration of the Input track, sets
     * the position of the input reading to that of the seconds.
     */
    void seek(double seconds) override;

    /**
     * Says if reading of input reached end of file.
     */
    bool reachedEOF() const override;

    /**
     * Gives sample specifications of input.
     */
    SampleFormat getSampleFormat() const override { return _sampleFormat; }

    /**
     * Gets the duration, in seconds, of the wav audio stored in this WavInput object.
     */
    double getDuration() const override;

private:
    std::string _filename;
    std::ifstream _file;

    SampleFormat _sampleFormat;

    std::streampos _dataPosition;  // Starting position of the PCM data 
    size_t _dataSize;              // Number of bytes of PCM data

    enum FormatCode {
        waveFormatPCM        = 0x0001,
        waveFormatIEEEFloat  = 0x0003,
        waveFormatAlaw       = 0x0006,
        waveFormatMulaw      = 0x0007,
        waveFormatExtensible = 0xFFFE,
    };

    // HELPER METHODS

    /**
     * Reads the RIFF subchunk of the WAV file. Checks it is correctly formatted
     * and leaves the _file stream pointing to the next subchunk.
     * The filesize will contain the size of the wav file, read in the subchunk.
     * If the file does not contain the WAV format, false is returned.
     * Otherwise returns true.
     */
    bool readRIFFChunk();

    /**
     * Read the Format subchunk of the WAV file. Cheks it is correctly formatted
     * and builds the _sampleFormat member. It leaves the _file stream
     * pointing to the next subchunk (data chunk).
     * If the subchunk is not propperly formated, returns false.
     * Otherwise returns true.
     */
    bool readFormatChunk();

    /**
     * Reads data chunk id and size and lives file stream pointing 
     * to the start of PCM data.
     */
    bool readDataChunkHeader();

    /**
     * Reads a integer of size 2 bytes (16 bits) from a LittleEndian input 
     * stream is, which has been opened in input binary mode.
     * An error may occur in the reading and must be checked by the caller.
     * TODO: move it to an utility class or to Input class.
     */
    uint16_t readLE16(std::istream& is);

    /**
     * Reads a integer of size 4 bytes (32 bits) from a LittleEndian input 
     * stream is, which has been opened in input binary mode.
     * An error may occur in the reading and must be checked by the caller.
     * TODO: move it to an utility class or to Input class.
     */
    uint32_t readLE32(std::istream& is);
};



}  // namespace player


#endif  // _VPLAYER_WAV_INPUT_H
