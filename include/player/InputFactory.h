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

#include "Input.h"


namespace player {


class InputFactory {
public:
    static std::unique_ptr<Input> create(std::string filename);

    static std::string getExtension(std::string filename);
};



}  // namespace player


#endif  // _VPLAYER_INPUT_FACTORY_H
