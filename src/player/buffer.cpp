// Buffer.cpp
//
// Module: player
//
// Implementation of the Buffer class.
//


#include "buffer.h"


namespace player {


Buffer::Buffer(int numChunks, int chunkSize, int minWriteSize, int dataAlign)
    : _numChunks{numChunks}, _chunkSize{chunkSize}, 
      _minWriteSize{minWriteSize}, _dataAlign{dataAlign},
      _writeChunk{0}, _readChunk{0} {}



// TODO: is a stub.
Buffer::Position Buffer::getWritePosition() const {
    return {};
}


// TODO: is a stub.
Buffer::Position Buffer::getReadPosition() const {
    return {};
}

// TODO: is a stub.
void Buffer::reset() {
    return;
}


// TODO: is a stub.
void Buffer::markRead() {
    return;
}


// TODO: is a stub.
void Buffer::markWritten() {
    return;
}



}  // namespace player
