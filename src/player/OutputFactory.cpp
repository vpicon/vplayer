/**
 * OutputFactory.cpp
 *
 * Module: player
 *
 * Implements the OutputFactory class methods.
 *
 */

#include "OutputFactory.h"
#include "Output.h"
#include "output_plugins/PulseaudioOutput.h"


namespace player {



std::unique_ptr<Output> OutputFactory::create() {
    std::unique_ptr<Output> outputPtr { new PulseaudioOutput{} };


    return outputPtr;
}





}  // namespace player
