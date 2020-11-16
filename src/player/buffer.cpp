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


/*
// TODO: is a stub.
Buffer::Position Buffer::getWritePosition() const {
    Chunk chunk {};
    Buffer::Position pos {chunk, 0, 0};
    return pos;
}


// TODO: is a stub.
Buffer::Position Buffer::getReadPosition() const {
    // TODO: is a stub.
    Chunk chunk {};
    Buffer::Position pos {chunk, 0, 0};
    return pos;
}
*/

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


// Buffer::Position Nested Class

/*
Buffer::Position(Chunk& chunk, int offset, int availableData)
    : _theChunk{chunk}, _bufferOffset{offset}, _availableData{availableData} {}

char *Buffer::Position::toCharPointer() {
    // Array has contiguous elements in memory thus is an alias to a 
    // pointer to its elements and the type can be reinterpreted.
    return reinterpret_cast<char *>( &(_theChunk[_bufferOffset]) );
}
*/



}  // namespace player
