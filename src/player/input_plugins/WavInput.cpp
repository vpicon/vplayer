/**
 * WavInput.cpp
 *
 * Module: player
 *
 * Implements WavInput class interface.
 *
 */

#include "input_plugins/WavInput.h"
#include "SampleFormat.h"
#include "Buffer.h"

#include <string>
#include <fstream>
#include <iostream>
#include <cstdint>


namespace player {


// TODO: define specific error types
WavInput::WavInput(const std::string& filename, Buffer& buffer)
    : _filename{filename},
      _file{filename, std::ios_base::binary | std::ios_base::in},
      _buffer{buffer}
{
    if (!_file)      
        throw std::runtime_error("Could not open file: " + filename);  
    
    if (!readRIFFChunk())  
        throw std::runtime_error("Could not read RIFF format");

    if (!readFormatChunk())
        throw std::runtime_error("Could not read WAV format");

    if (!readDataChunkHeader()) 
        throw std::runtime_error("Could not read data header");
}



// TODO: is a stub.
size_t WavInput::read(Buffer::Position writePos) {
    // Check valid write position
    if (writePos.size() == 0 || writePos.toPointer() == nullptr)
        return 0;

    // Read from file to writePosition
    _file.read(writePos.toPointer(), writePos.size());

    // Check amount of bytes read and possible errors
    size_t nread = _file.gcount();
    if (_file.eof())
        _eof = true;

    // Mark buffer as written
    _buffer.markWritten(nread);

    // Return number of characters read
    return nread;
}



// TODO: is a stub.
void WavInput::seek(double seconds) {
    seconds = 0;
}



// TODO: is a stub.
bool WavInput::reachedEOF() const {
    return false;
}



double WavInput::getDuration() const {
    return (8.0 * _dataSize) / _sampleFormat.getBitrate();
}



bool WavInput::readRIFFChunk() {
    char buf[4];

    // Read RIFF
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "RIFF")
        return false;

    // Read file size
    uint32_t size = readLE32(_file);
    if (!_file)
        return false;
    size += 8;
    // TODO: record some form of error checking with 
    // size = fmtsize + datasize + const


    // Read WAVE
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "WAVE")
        return false;

    // RIFF Header Chunk read successfully
    return true;
}



bool WavInput::readFormatChunk() {  // TODO: refactor code
    char buf[4];

    // Read fmt 
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "fmt ")
        return false;

    // Read format chunk size
    uint32_t size = readLE32(_file);
    if (!_file || size != 16)  // TODO: Add support for other subformats 
        return false;

    // Read format code
    uint16_t formatCode = readLE16(_file);
    if (!_file || formatCode != FormatCode::waveFormatPCM) // TODO: add support for other types, such as float
        return false; 

    // Read num channels
    uint16_t numChannels = readLE16(_file);
    if (!_file || (numChannels != 1 && numChannels != 2)) // TODO: add support for more channels
        return false; 

    // Read sampling rate
    uint32_t frameRate = readLE32(_file);
    if (!_file)
        return false; 

    // Read data rate
    uint32_t byteRate = readLE32(_file);
    if (!_file)
        return false; 

    // Read block align 
    uint16_t blockSize = readLE16(_file);
    if (!_file)
        return false; 

    if (byteRate != blockSize * frameRate)  // TODO: make strategy for assuring invariants
        return false;

    // Read bit depth 
    uint16_t bitDepth = readLE16(_file);
    if (!_file)
        return false; 

    // Set sample format of WavInput object
    
    // Wav is unsigned only for bitdepths of 1 to 8
    SampleFormat::Encoding enc = (bitDepth == 8) ?            
                                  SampleFormat::Encoding::unsignedEnc : 
                                  SampleFormat::Encoding::signedEnc;
    // Wav is always little endian
    SampleFormat::Endian endian = SampleFormat::Endian::little;

    _sampleFormat = SampleFormat {static_cast<int>(frameRate),
                                  static_cast<int>(bitDepth),
                                  static_cast<int>(numChannels),
                                  endian,
                                  enc};

    // Format chunk read successfully
    return true;
}



bool WavInput::readDataChunkHeader() {
    char buf[4];

    // Read RIFF
    _file.read(buf, 4); 
    if (!_file || std::string {buf} != "data")
        return false;

    // Read data size
    uint32_t size = readLE32(_file);
    if (!_file)
        return false;
    _dataSize = size;

    // Keep starting position of PCM data
    _dataPosition = _file.tellg(); 
    
    // Data chunk header read successfully
    return true;
}



uint16_t WavInput::readLE16(std::istream& is) {
    uint16_t data;
    is.read(reinterpret_cast<char *>(&data), 2);
    return data;
}



uint32_t WavInput::readLE32(std::istream& is) {
    uint32_t data;
    is.read(reinterpret_cast<char *>(&data), 4);
    return data;
}




}  // namespace player
