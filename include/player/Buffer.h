/** 
 * Buffer.h  
 *
 * Module: player
 *
 * Definition of the Buffer class.
 *
 */

#ifndef _VPLAYER_BUFFER_H
#define _VPLAYER_BUFFER_H


#include <cstdint>
#include <vector>
#include <mutex>


namespace player {


/**
 * Buffer class containing a chunked circular buffer. 
 * A thread safe monitor object to read data from input in the producer 
 * class, and read data from output in the consumer class, two classes 
 * which will run in separate threads.
 * The user may read or write from/to one chunk at a time. Thus, the max 
 * amount it can be read/written on each call to a Buffer::Position depends 
 * on the size of the chunk.
 * TODO: document why is better chunked buffer than not
 */
class Buffer {
    /**
     * Represents a circular chunked buffer, stored in the buffer array.
     * Buffer = [Chunk][Chunk] ... [Chunk]
     * The Buffer uses one chunk to keep current of the write chunk and read
     * chunk.
     *
     * Invariants:
     *    0 <= (_readChunk, _writeChunk) < _numChunks
     *    The buffer is full, if and only if, 
     *       (_writeChunk + 1) % _numChunks == _readChunk
     *    All chunks before (in circular sense) the _writeChunk, have full flag set.
     *    Every chunk after (in circular sense) the _writeChunk, and before the 
     *       read chunk, it is at initial state (w = r = 0, full = false)
     *    _writeChunk always points to a non full chunk.
     */
public:
    // CONSTRUCTORS AND DESTRUCTORS 
    
    /**
     * Construcs a new empty buffer object.
     * @param nChunks: > 0, number of chunks in the buffer
     * @param chunkSize: > 0, the size of the inner buffer of each chunk
     * @param minWriteSize: is the minimum size we expect to get for a 
     *        new call to the write position in the buffer.
     *        It must be 0 <= minWriteSize < chunkSize, the greater it is, the 
     *        more space is wasted in the chunk. But being 0, we may end up 
     *        doing calls to the buffer where only a few bytes are written.
     * @param dataAlign: data inside the chunk is aligned, intended to be
     *        aligned by the size of PCM frames.
     */
    Buffer(size_t numChunks,    size_t chunkSize, 
           size_t minWriteSize, size_t dataAlign = 1);
    ~Buffer() {};

    Buffer& operator=(const Buffer&) = delete; // Disallow copy
    Buffer(const Buffer&)            = delete; // Disallow copy constructor

    Buffer& operator=(Buffer&&) = delete; // Disallow move
    Buffer(Buffer&&)            = delete; // Disallow move constructor


    // CLASS CONSTANTS AND TYPES
    
    /**
     * Class pointing to a position inside the buffer. It contains a pointer to
     * such position; and an integer, which counts the available data in the 
     * buffer if such position is for reading; or the available space, if such 
     * position is for writting.
     */
    class Position;
    

    // ACCESSORS

    /**
     * Gives a Buffer::Position object to which it can be read some data,
     * the quantity indicated by such ReadPosition object.
     * Since the Buffer object is chunked, no more than chunkSize data can
     * be available each call, thus the method may be called several times to
     * read an arbitrary number of data.
     * If no data is available, the position contains a nullpointer and a count
     * of 0.
     */
    Buffer::Position getReadPosition();

    /**
     * Gives a Buffer::WritePosition object to which it can be written some 
     * data, the quantity indicated by such Position object.
     * Since the Buffer object is chunked, no more than chunkSize free space can
     * be available each call, thus the method may be called several times to
     * write an arbitrary number of data.
     * It is assured though, that at least minWriteSize bytes of space are 
     * available on each call, assuming there is space left on the buffer; in 
     * such case, the position is marked to have 0 available data in it, and 
     * a null pointer.
     */
    Buffer::Position getWritePosition();

    /**
     * Returns the number of chunks considered filled.
     */
    inline size_t filledChunks() const { return _fullChunks; }


    // MUTATORS

    /**
     * Sets the buffer object to its initial state, all chunks are emptied and 
     * with no data written in it.
     */
    void reset();

    /**
     * After reading the data stored in the buffer at ReadPosition object obtained
     * in a call to getReadPosition, such data must be marked as read by calling
     * the function, in order to get next available data in the buffer.
     *
     * Undefined behaviour occurs when the function is called with an arbitrary
     * number of data.
     */
    void markRead(size_t n);

    /**
     * After writing to the buffer at a WritePosition object obtained in a call 
     * to getReadPosition, such data must be marked as read by calling the function,
     * in order to get next available data in the buffer.
     *
     * Undefined behaviour occurs when the function is called with an arbitrary
     * number of data.
     */
    void markWritten(size_t n);

    /**
     * Set the align size of the buffer.
     */
    inline void setAlign(size_t alignSize) { _dataAlign = alignSize; }

private:

    /**
     * Structure representing each of the inner chunks of the total buffer.
     * Each chunk is a linear buffer, where chunkSize bytes can be stored in. 
     * The index r marks the position where data can be read from. Index w 
     * marks the position where data can be written to. Full if the buffer was
     * filled up previously.
     * 
     * Invariants:
     *   0 <= r <= w <= _chunkSize
     *   w points to a valid position to write if and only if w < _chunkSize
     *   r points to data to be read if and only if  r < w
     *   full == true, if and only if, w > _chunkSize - _minWriteSize
     */
    struct Chunk {
        std::vector<char> buf;
        size_t w;
        size_t r;
        bool full;
    };

    const size_t _numChunks;  
    const size_t _chunkSize; 
    const size_t _minWriteSize; 
    size_t _dataAlign; 

    size_t _writeChunk = 0;
    size_t _readChunk  = 0;
    size_t _fullChunks  = 0;

    std::vector<Chunk> _buffer;

    std::mutex _bufferMutex;
};



class Buffer::Position {
public:
    friend class Buffer;

    /**
     * Returns a char pointer to the inner position in the buffer with size 
     * contiguous bytes which can be used to store or read data.
     * Useful to use with low level functions, such as output C libs.
     */
    char *toPointer(); 

    /**
     * Gives amount of data which could be read or written in the position
     * pointed by this object.
     */
    inline size_t size() { return _size; }  
private:
    /**
     * Private constructor to not expose internals of the buffer.
     * Caller only needs to get size and pointer to which wirte/read.
     */
    Position(Chunk& chunk, size_t offset, size_t size)
        : _chunk{chunk}, _offset{offset}, _size{size} {}  

    Chunk& _chunk;
    size_t _offset;
    size_t _size;
};




}  // namespace player


#endif  // _VPLAYER_BUFFER_H
