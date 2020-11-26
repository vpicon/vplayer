/**
 * Producer.h
 *
 * Module: player
 *
 * Defines Producer class interface.
 *
 */

#ifndef _VPLAYER_PRODUCER_H
#define _VPLAYER_PRODUCER_H

#include "Buffer.h"
#include "Input.h"

#include <memory>
#include <string>
#include <mutex>
#include <condition_variable>


namespace player {


class Producer {
    /**
     * Class Producer responsible to create audio data and storing it
     * in the buffer (for the Consumer to use it for playback).
     *
     * Class invariants:
     *       _input points to a vaild Input Object iff _status is 
     *          producing, paused or stopped.
     *       if _status is stopped, then the _buffer is empty (reseted)
     */
public:
    enum class Status { producing, paused, stopped, unloaded, exit };

    Producer(Buffer& buffer);

    ~Producer();

    /**
     * Sets a new track to be played.
     */
    void setTrack(std::string filename);
        

    /**
     * Sets the status to produce, for the class to main loop to start
     * producing data.
     */
    void produce();

    /**
     * Sets the status to paused, for the class to main loop to pause
     * producing data.
     */
    void pause();

    /**
     * Sets the status to stop, for the class to main loop to stop
     * producing data and clean buffers.
     */
    void stop();

    /**
     * Sets status to exit, for the producer thread to stop running.
     */
    void exit();


    /**
     * Obtain current status of Consumer.
     */
    Status getStatus() { return _status; }


    /**
     * Obtains the Sample Format of the currently loaded input object.
     */
    SampleFormat getCurrentSampleFormat() { return _input->getSampleFormat(); }


    /**
     * Main loop of the Producer run in a separate thread.
     */
    void run();

private:
    Buffer& _buffer;
    Status  _status;

    std::unique_ptr<Input> _input;

    std::mutex _prodMutex;
    std::condition_variable _prodStateCV;


    /**
     * Changes the status of this producer object and signals other
     * waiting threads that the state changed.
     */
    void setStatus(Status s);
};




}  // namespace player


#endif  // _VPLAYER_PRODUCER_H
