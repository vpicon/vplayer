/**
 * Consumer.cpp
 *
 * Module: player
 *
 * Implements Consumer class. 
 *
 */

#include "Consumer.h"
#include "Buffer.h"

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>



namespace player {



Consumer::Consumer(Buffer& buffer)
    : _buffer{buffer},
      _status{Status::unloaded},
      _output{}
{
}



Consumer::~Consumer()
{
}



// TODO: is a stub.
void Consumer::consume() {
    return;
}



// TODO: is a stub.
void Consumer::pause() {
    return;
}



// TODO: is a stub.
void Consumer::stop() {
    return;
}



// TODO: is a stub.
void Consumer::run() {
    return;
}



void Consumer::setStatus(Consumer::Status s) {
    _status = s;
    _consStateCV.notify_one(); 
}




}  // namespace player
