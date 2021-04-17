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


#include "PlayerMediator.h"
#include "Producer.h"
#include "Consumer.h"
#include "Buffer.h"
#include "Tracklist.h"



namespace player {



/**
 * Player interface class.
 */
class Player {
public:
    enum class Status { playing, paused, stopped };

    Player();

    void unpause();
    void pause();
    void stop();

    void playTracklist(Tracklist tl);

private:
    Buffer   _buffer;
    Producer _producer;
    Consumer _consumer;
    PlayerMediator _mediator;
    
    Status _status = Status::stopped;

    // Tracklist _tl;
};


void bind(PlayerMediator& mediator, Producer& producer);
void bind(PlayerMediator& mediator, Consumer& consumer);


}  // namespace player


#endif  // _VPLAYER_PLAYER_H
