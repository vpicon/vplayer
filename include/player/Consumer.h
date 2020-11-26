/**
 * Consumer.h
 *
 * Module: player
 *
 * Defines Consumer class interface.
 *
 */

#ifndef _VPLAYER_CONSUMER_H
#define _VPLAYER_CONSUMER_H


#include "Buffer.h"
#include "Output.h"

#include <memory>
#include <mutex>
#include <condition_variable>


namespace player {



class Consumer {
public:
    enum class Status { consuming, paused, stopped, unloaded, exit };

    Consumer(Buffer& buffer);

    ~Consumer();
        

    /**
     * Sets the status to consume, for the class to main loop to start
     * consuming data.
     */
    void consume();

    /**
     * Sets the status to paused, for the class to main loop to pause
     * consuming data.
     */
    void pause();

    /**
     * Sets the status to stop, for the class to main loop to stop
     * consuming data, and clean buffers.
     */
    void stop();


    /**
     * Obtain current status of Consumer.
     */
    Status getStatus() { return _status; }


    /**
     * Main loop of the Consumer run in a separate thread.
     */
    void run();

private:
    Buffer& _buffer;
    Status  _status;

    std::unique_ptr<Output> _output;

    std::mutex _consMutex;
    std::condition_variable _consStateCV;


    /**
     * Changes the status of this producer object and signals other
     * waiting threads that the state changed.
     */
    void setStatus(Status s);
};



}  // namespace player


#endif  // _VPLAYER_CONSUMER_H
