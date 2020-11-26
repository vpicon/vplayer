/**
 * Player.h
 *
 * Module: player
 *
 * Defines Player class interface.
 *
 */

#ifndef _VPLAYER_PLAYER_H
#define _VPLAYER_PLAYER_H


#include "Buffer.h"
#include "Producer.h"
#include "Consumer.h"


namespace player {



class Player {
public:
    enum class Status { playing, paused, stopped };

    Player();
    ~Player() {}

    void play();
    void pause();
    void stop();

    void playTrack();

private:
    Buffer   _buffer;
    Producer _producer;
    Consumer _consumer;
    
    Status _status = Status::stopped;
};




}  // namespace player


#endif  // _VPLAYER_PLAYER_H
