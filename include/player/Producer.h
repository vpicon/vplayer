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



namespace player {


class Producer {
public:
    enum class Status { consuming, paused, stopped, unloaded };

    Consumer(Buffer& buffer): _buffer{buffer} {}
    ~Player() {}

    void consume();
    void pause();
    void stop();

    Status getStatus();
    void setStatus(Status s) { _status{s}; }

    void setTrack();

private:
    Buffer& _buffer;
    Status  _status;
};




}  // namespace player


#endif  // _VPLAYER_PRODUCER_H
