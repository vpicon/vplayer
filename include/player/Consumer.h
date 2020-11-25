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


namespace player {



class Consumer {
public:
    enum class Status { consuming, paused, stopped, unloaded, exit };

    Consumer(Buffer& buffer): _buffer{buffer} {}
    ~Consumer() {}

    void consume();
    void pause();
    void stop();

    Status getStatus();
    void setStatus(Status s) { _status = s; }

    void setTrack();

private:
    Buffer& _buffer;
    Status  _status = Status::unloaded;
};



}  // namespace player


#endif  // _VPLAYER_CONSUMER_H
