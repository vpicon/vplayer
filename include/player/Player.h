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

    Player() {}
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


/** Temporal Stuff 

    // The size has to be a multiple of the frame size. We can then chose the 
    // lcm of all available frame sizes, which is the product of bit size and 
    // channel size.
    //     (BITS):     the lcm of 1, 2, 3, 4 (8, 16, 24, and 32 bits) is 12.
    //     (CHANNELS): the lcm of 1, 2  is 2.
    // We can then adjust the chunk Size by any reasonable factor to make the 
    // chunk sufficiently big but not too small.
    static constexpr int _chunkSize = 2 * 12 * 1024; 
    // 10 seconds worth of data may be stored in the buffer. Considering the 
    // typical frame rate 44100 frames per second, number of samples per frame, 
    // may be something about 4 * 2. 
    static constexpr size_t _numChunks = 10 * 44100 * 4 * 2 / _chunkSize;  

    static const int _minWriteSize = 1024; 
    const int _dataAlign; 
    */

}  // namespace player


#endif  // _VPLAYER_PLAYER_H
