/**
 * Buffer.cpp
 *
 * Module: player
 *
 * Implementation of the Buffer class.
 */


#include "buffer.h"


namespace player {


Buffer::Buffer(size_t numChunks, size_t chunkSize, 
               size_t minWriteSize, size_t dataAlign)
    : _numChunks{numChunks}, _chunkSize{chunkSize}, 
      _minWriteSize{minWriteSize}, _dataAlign{dataAlign},
      _writeChunk{0}, _readChunk{0} {}



// TODO: is a stub.
Buffer::Position Buffer::getWritePosition() const {
    return {nullptr, 0, 0};
}


// TODO: is a stub.
Buffer::Position Buffer::getReadPosition() const {
    return {nullptr, 0, 0};
}


// TODO: is a stub.
size_t Buffer::filledChunks() {
    return 0;
}


// TODO: is a stub.
void Buffer::reset() {
    return;
}


// TODO: is a stub.
void Buffer::markRead(size_t n) {
    n = 0;
    return;
}


// TODO: is a stub.
void Buffer::markWritten(size_t n) {
    n = 0;
    return;
}



}  // namespace player
