/**
 * Producer.cpp
 *
 * Module: player
 *
 * Implements Producer class. 
 *
 */

#include "Producer.h"
#include "Buffer.h"
#include "InputFactory.h"

#include <string>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>



namespace player {



Producer::Producer(Buffer& buffer)
    : _buffer{buffer},
      _status{Status::unloaded},
      _input{}
{
}


Producer::~Producer()
{
}



// TODO: is a stub.
void Producer::produce() {
    if (_status == Status::paused || _status == Status::stopped) {
        setStatus(Status::producing);
    }
}



// TODO: is a stub.
void Producer::pause() {
    if (_status == Status::producing) {
        setStatus(Status::paused);   
    }
}



// TODO: is a stub.
void Producer::stop() {
    if (_status == Status::producing || _status == Status::paused) {
        _buffer.reset();
        setStatus(Status::stopped);
    }
}



// TODO: is a stub.
void Producer::setTrack(std::string filename) {
    // Acquire the producer lock
    std::lock_guard<std::mutex> lck{_prodMutex};

    // Create a new input object (ptr) from filename
    _input = InputFactory::create(filename);

    // Change status to stopped
    switch (_status) {
        case Status::paused:
        case Status::producing:
            _buffer.reset();
            // Fall through
        case Status::unloaded:
            setStatus(Status::stopped);
            break;

        default:
            break;
    }
}



void Producer::run() {
    while (true) {
        if (_status == Status::exit)
            // Exit loop
            break;

        std::unique_lock<std::mutex> lck{_prodMutex};
        // Producing data
        if (_status == Status::producing) {
            player::Buffer::Position wPos = _buffer.getWritePosition(); 
            if (wPos.size() == 0) {  // Buffer full
                std::this_thread::sleep_for(std::chrono::milliseconds {1});
                continue;
            }

            size_t nread = _input->read(wPos);
            _buffer.markWritten(nread);

            if (nread == 0) { // May reached end of file
                if (_input->reachedEOF())
                    return;
            }

            continue;
        }

        // Not producing state
        if (_status == Status::stopped ||
            _status == Status::paused  ||
            _status == Status::unloaded)
        {
            _prodStateCV.wait(lck);
            continue;
        }
    }
}



void Producer::setStatus(Producer::Status s) {
    _status = s;
    _prodStateCV.notify_one(); 
}




}  // namespace player
