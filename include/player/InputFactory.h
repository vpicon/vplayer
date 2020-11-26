/**
 * InputFactory.h
 *
 * Module: player
 *
 * Defines InputFactory class interface to create Input subclasses
 * of the Input interface.
 * Uses the SimpleFactory pattern.
 *
 */

#ifndef _VPLAYER_INPUT_FACTORY_H
#define _VPLAYER_INPUT_FACTORY_H


#include <memory>
#include <string>
#include <vector>

#include "Input.h"


namespace player {


class InputFactory {
public:
    static std::unique_ptr<Input> create(std::string filename);

    /**
     * Given a filename returns a string containing the extension of
     * such filename. If the given filename is invalid (does not contain
     * an extension, contains an invalid extension ...), returns the
     * empty string "".
     *
     * Supported extensions: wav, mp3.
     */
    static std::string getExtension(std::string filename);

    static const inline std::vector<std::string> supportedExtensions {"wav", 
                                                                      "flac", 
                                                                      "mp3"};

private:
    /**
     * Tells if the given extension is a supported extension.
     */
    bool isSupportedExtension(std::string extension);
};




}  // namespace player


#endif  // _VPLAYER_INPUT_FACTORY_H
