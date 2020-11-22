/**
 * Buffer.cpp
 *
 * Module: player
 *
 * Implementation of the Buffer class.
 *
 */


#include "Buffer.h"

#include <cstdint>
#include <mutex>


namespace player {



// The _numChunks, will be 1 chunk larger than the given value by the caller, 
// since we will need one extra index to implement the circular buffer; 
// but the user has to see the buffer having numChunks chunks, with each
// chunkSize bytes in size.
Buffer::Buffer(size_t numChunks, size_t chunkSize, 
               size_t minWriteSize, size_t dataAlign)
    : _numChunks {numChunks + 1},
      _chunkSize {chunkSize},
      _minWriteSize {minWriteSize}, 
      _dataAlign {dataAlign},
      _buffer( _numChunks, Chunk{std::vector<char>(_chunkSize), 0, 0, false} )
{
}



Buffer::Position Buffer::getWritePosition() {
    // Lock buffer mutex
    std::lock_guard<std::mutex> lck{_bufferMutex};

    // Current chunk
    Chunk& chunk = _buffer[_writeChunk]; 

    // Return read position
    size_t size = ((_writeChunk + 1) % _numChunks != _readChunk) ? 
                    _chunkSize - chunk.w : 0;

    return Position {chunk, chunk.w, size};
}



Buffer::Position Buffer::getReadPosition() {
    // Lock buffer mutex
    std::lock_guard<std::mutex> lck{_bufferMutex};

    // Current chunk
    Chunk& chunk = _buffer[_readChunk]; 

    // Return read position
    size_t available = chunk.w - chunk.r;  // Available data to read

    return Position {chunk, chunk.r, available};
}



void Buffer::reset() {
    // Lock buffer mutex
    std::lock_guard<std::mutex> lck{_bufferMutex};

    // Reset each chunk
    for (Chunk& chunk : _buffer) {
        chunk.w    = 0;
        chunk.r    = 0;
        chunk.full = false;
    }

    // Reset buffer state
    _writeChunk = 0;
    _readChunk  = 0;
    _fullChunks = 0;
}



void Buffer::markRead(size_t n) {
    // Lock buffer mutex
    std::lock_guard<std::mutex> lck{_bufferMutex};

    // Current chunk
    Chunk& chunk = _buffer[_readChunk]; 

    // Increment n the w of the reading chunk
    chunk.r += n;

    // Update chunk and buffer state
    if (chunk.full && chunk.w == chunk.r) {
        // Reset the current pointing chunk
        chunk.full = false;
        chunk.r    = 0;
        chunk.w    = 0;

        _fullChunks--;
        // Point to next chunk for reading
        _readChunk = (_readChunk + 1) % _numChunks;
    }
}



void Buffer::markWritten(size_t n) {
    // Lock buffer mutex
    std::lock_guard<std::mutex> lck{_bufferMutex};

    // Current chunk
    Chunk& chunk = _buffer[_writeChunk]; 

    // Increment n the w of the reading chunk
    chunk.w += n;

    // Update buffer and chunk state
    if (chunk.w > _chunkSize - _minWriteSize) {
        // Set chunk as full and point to next chunk
        chunk.full = true;
        _fullChunks++;
        _writeChunk = (_writeChunk + 1) % _numChunks;
    }
}



char *Buffer::Position::toPointer() {
    return (_size == 0) ?
            nullptr     :
            reinterpret_cast<char *>(&(_chunk.buf[_offset]));
}



}  // namespace player
