/**
 * Player.cpp
 *
 * Module: player
 *
 * Implements the Player class.
 *
 */

#include "Player.h"


namespace player {



// The size has to be a multiple of the frame size. We can then chose the 
// lcm of all available frame sizes, which is the product of bit size and 
// channel size.
//     (BITS):     the lcm of 1, 2, 3, 4 (8, 16, 24, and 32 bits) is 12.
//     (CHANNELS): the lcm of 1, 2  is 2.
// We can then adjust the chunk Size by any reasonable factor to make the 
// chunk sufficiently big but not too small.
static constexpr int chunkSize = 2 * 12 * 1024;
// 10 seconds worth of data may be stored in the buffer. Considering the 
// typical frame rate 44100 frames per second, number of bytes per frame, 
// may be something about 4 * 2. 
static constexpr size_t numChunks = 10 * 44100 * 4 * 2 / chunkSize;  
static constexpr int minWriteSize = 1024; 


Player::Player():
    _buffer{numChunks, chunkSize, minWriteSize},
    _producer{_buffer},
    _consumer{_buffer}
{
}


// TODO: is a stub
void Player::unpause() {
    return;
}


// TODO: is a stub
void Player::pause() {
    return;
}


// TODO: is a stub
void Player::stop() {
    return;
}


// TODO: is a stub
void Player::playTracklist(Tracklist tl) {
    return;
}


void bind(PlayerMediator& mediator, Producer& producer) {
    mediator._producer = &producer;
    // producer._mediator = &mediator;
}


}  // namespace player
