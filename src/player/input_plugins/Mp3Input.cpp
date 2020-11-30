/**
 * Mp3Input.cpp
 *
 * Module: player
 *
 * Implements Mp3Input class interface.
 *
 */

#include "input_plugins/Mp3Input.h"
#include "SampleFormat.h"
#include "Buffer.h"

#include <string>


namespace player {


// TODO: change order buffer filename
// TODO: define specific error types
Mp3Input::Mp3Input(const std::string& filename)
    : _filename{filename}
{
    int rc;
    bool isInit, isHandle, isOpen;
    
    isInit = true;
    // Initiate mpg123 library
    if ((rc = mpg123_init()) != MPG123_OK) {
        cleanup(isInit);
        std::runtime_error("Could not initiate mpg123: " + 
                           std::string{ mpg123_plain_strerror(rc) });
    }
    
    isHandle = true;
    // Create an mpg123 obscure handle
    _handle = mpg123_new(nullptr /* default decoder */, &rc);
    if (_handle == nullptr) {
        cleanup(isInit, isHandle);
        std::runtime_error("Could not create mpg123 handle: " + 
                           std::string{ mpg123_plain_strerror(rc) });
    }

    isOpen = true;
    // Open the file with mpg123
    if ((rc = mpg123_open(_handle, _filename.c_str())) != MPG123_OK) {
        cleanup(isInit, isHandle, isOpen);
        std::runtime_error("Could not open file: " + 
                           std::string{ mpg123_plain_strerror(rc) });
    }

    // Get sample format of the audio data
    long rate;
    int channels, encoding;
    if ((rc = mpg123_getformat(_handle, &rate, &channels, &encoding)) != MPG123_OK) {
        cleanup(isInit, isHandle, isOpen);
        std::runtime_error("Could not get format from input: " + 
                           std::string{ mpg123_plain_strerror(rc) });
    }

    _sampleFormat = SampleFormat{static_cast<int>(rate),
                                 channels,
                                 0, 
                                 SampleFormat::Endian::little,
                                 SampleFormat::Encoding::signedEnc};
}



// TODO: is a stub
Mp3Input::~Mp3Input() 
{
    bool init{true}, handle{true}, open{true};
    cleanup(init, handle, open);
}



// TODO: is a stub
size_t Mp3Input::read(Buffer::Position writePos) {
    return 0;
}



// TODO: is a stub
void Mp3Input::seek(double seconds) {
}



// TODO: is a stub
bool Mp3Input::reachedEOF() const {
    return _eof;
}



// TODO: is a stub
double Mp3Input::getDuration() const {
    return 0.0;
}



/**
 * Define this C-style cleanup routine to ensure that cleanup is done 
 * in the right order if we exit constructor by failure. For example,
 * we free the handle before we exit the mpg123 library.
 */
void Mp3Input::cleanup(bool init, bool handle, bool open) {
    // Close opened files by mpg123
    if (open)
        mpg123_close(_handle);
    // Free resources allocated by handle
    if (handle)
        mpg123_delete(_handle);
    // Exit mpg123 library
    if (init)
        mpg123_exit();
}




}  // namespace player
