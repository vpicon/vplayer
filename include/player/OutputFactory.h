/**
 * OutputFactory.h
 *
 * Module: player
 *
 * Defines OutputFactory class interface to create Output subclass 
 * instances of the Output interface.
 * Uses the SimpleFactory pattern.
 *
 */

#ifndef _VPLAYER_OUTPUT_FACTORY_H
#define _VPLAYER_OUTPUT_FACTORY_H


#include <memory>


#include "Output.h"


namespace player {


class OutputFactory {
public:
    static std::unique_ptr<Output> create();
};




}  // namespace player


#endif  // _VPLAYER_OUTPUT_FACTORY_H
