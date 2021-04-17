/**
 * PlayerMediator.h
 *
 * Module: player
 *
 * Defines PlayerMediator class interface.
 *
 */

#ifndef _VPLAYER_PLAYER_MEDIATOR_H
#define _VPLAYER_PLAYER_MEDIATOR_H


#include "Buffer.h"
#include "Tracklist.h"


namespace player {


class Producer;
class Consumer;


/**
 * PlayerMediator class.
 */
class PlayerMediator {
public:
    PlayerMediator();

private:
    Producer* _producer {nullptr};
    Consumer* _consumer {nullptr};

    // Global friend functions to implement bidirectional associations
    // between PlayerMediator and Consumer/Producer
    friend void bind(PlayerMediator& mediator, Producer& producer); 
    friend void bind(PlayerMediator& mediator, Consumer& consumer);
};




}  // namespace player


#endif  // _VPLAYER_PLAYER_MEDIATOR_H
