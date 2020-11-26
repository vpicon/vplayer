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
#include "Output.h"
#include "OutputFactory.h"

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>



namespace player {



Consumer::Consumer(Buffer& buffer)
    : _buffer{buffer},
      _status{Status::unloaded},
      _output{OutputFactory::create()}
{
}



Consumer::~Consumer()
{
}



void Consumer::consume() {
    if (_status == Status::paused || _status == Status::stopped)
        setStatus(Status::consuming);
}



void Consumer::pause() {
    if (_status == Status::consuming)
        setStatus(Status::consuming);
}



// TODO: is a stub
void Consumer::exit() {
    setStatus(Status::exit);
}



void Consumer::stop() {
    if (_status == Status::consuming || _status == Status::paused) {
        _buffer.reset();
        setStatus(Status::stopped);
    }
}



void Consumer::setStatus(Consumer::Status s) {
    _status = s;
    _consStateCV.notify_one(); 
}



void Consumer::openOutput(SampleFormat sf) {
    // Protect the output object from being accessed from
    // two different threads.
    std::lock_guard<std::mutex> lck{_consMutex};

    // Check if already opened output connections
    if (_status == Status::consuming ||
        _status == Status::paused    || 
        _status == Status::stopped) {
        _output->close();
    }

    // Open new connection with output and go stopped
    _output->open(sf);
    setStatus(Status::stopped);
}



void Consumer::run() {
    while (true) {
        if (_status == Status::exit) 
            // Exit loop
            break;

        std::unique_lock<std::mutex> lck{_consMutex};
        // Consuming data
        if (_status == Status::consuming) {
            player::Buffer::Position rPos = _buffer.getReadPosition();
            if (rPos.size() == 0) // Empty buffer, try again
                continue;

            size_t nwritten = _output->write(rPos);
            _buffer.markRead(nwritten);

            if (nwritten == 0) {
                if (_output->outSpace() == 0) {
                    std::this_thread::sleep_for(std::chrono::milliseconds {1});
                }
            }

            continue;
        }

        // Not Consuming data
        if (_status == Status::paused  ||
            _status == Status::stopped ||
            _status == Status::unloaded ) {
            _consStateCV.wait(lck);
            continue;
        }
    }
}




}  // namespace player
