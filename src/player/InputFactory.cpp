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

#include <string>

namespace player {



std::unique_ptr<Input> InputFactory::create(std::string filename) {
    std::unique_ptr<Input> inputPtr;

    std::string ext = InputFactory::getExtension(filename);
    if (ext == "wav") 
        inputPtr.reset(new WavInput{filename});

    return inputPtr;
}



std::string InputFactory::getExtension(std::string filename) {
    return filename;
}



}  // namespace player
