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


namespace player {


class Producer {
public:
    enum class Status { producing, paused, stopped, unloaded, exit };

    Producer(Buffer& buffer);
    ~Producer() {}


    /**
     * Sets the status to produce, for the class to main loop to start
     * producing data.
     */
    void produce();

    void pause();

    void stop();


    inline Status getStatus() { return _status; }

    inline void setStatus(Status s) { _status = s; }


    void setTrack(std::string filename);
        

private:
    Buffer& _buffer;
    Status  _status {Status::unloaded};

    std::unique_ptr<Input> _input;
};




}  // namespace player


#endif  // _VPLAYER_PRODUCER_H
