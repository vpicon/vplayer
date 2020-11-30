/**
 * InputFactory.cpp
 *
 * Module: player
 *
 * Implements the InputFactory class methods.
 *
 */

#include "InputFactory.h"
#include "input_plugins/WavInput.h"
#include "input_plugins/Mp3Input.h"

#include <string>
#include <regex>

namespace player {



std::unique_ptr<Input> InputFactory::create(std::string filename) {
    std::unique_ptr<Input> inputPtr;

    std::string ext = InputFactory::getExtension(filename);
    if (ext == "wav") 
        inputPtr.reset(new WavInput{filename});
    if (ext == "mp3")
        inputPtr.reset(new Mp3Input{filename});

    return inputPtr;
}



std::string InputFactory::getExtension(std::string filename) {
    std::string extension {};

    std::smatch m {};
    std::regex pattern {".+(\\.[[:alnum:]]+)$"};

    if (std::regex_search(filename, m, pattern))
        // Get the extension from submatch, without the dot (.)
        extension = m[1].str().substr(1);

    return (isSupportedExtension(extension)) ?
            extension : 
            "";
}



bool InputFactory::isSupportedExtension(std::string extension) {
    std::set<std::string>::const_iterator it = supportedExtensions.find(extension); // TODO: put auto
    
    return it != supportedExtensions.end();
}




}  // namespace player
