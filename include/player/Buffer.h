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


namespace player {


/**
 * Buffer class containing a chunked circular buffer. 
 * A thread safe monitor object to read data from input in the producer class, 
 * and read data from output in the consumer class, two classes which will run 
 * in separate threads.
 * TODO: document why is better chunked buffer than not
 */
class Buffer {
    /**
     * TODO:
     * Represents a circular chunked buffer, stored in the buffer array.
     * Buffer = [Chunk][Chunk] ... [Chunk]
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
    Buffer::Position getReadPosition() const;

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
    Buffer::Position getWritePosition() const;

    /**
     * Returns the number of chunks considered filled.
     */
    size_t filledChunks() const;


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
    const size_t _numChunks;  
    const size_t _chunkSize; 
    const size_t _minWriteSize; 
    size_t _dataAlign; 

    int _writeChunk, _readChunk;   


    /**
     * Structure representing each of the inner chunks of the total buffer.
     * Each chunk is itself a circular buffer, where chunkSize bytes can be 
     * stored in. 
     */
    struct Chunk {
        std::vector<char> buf;
        int w;
        int r;
    };
    
};



class Buffer::Position {
public:
    Position(Chunk *chunk, int offset, size_t size)
        : _chunk{chunk}, _offset{offset}, _size{size} {}

    /**
     * Returns a char pointer to the inner position in the buffer with size 
     * contiguous bytes which can be used to store or read data.
     * Useful to use with low level functions, such as output C libs.
     */
    inline char *toPointer() { return nullptr; }  // TODO: Is a stub

    /**
     * Gives amount of data which could be read or written in the position
     * pointed by this object.
     */
    inline size_t size() { return _size; }  // TODO: Is a stub
private:
    Chunk* _chunk;
    int    _offset;
    size_t _size;
};



}  // namespace player






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



#endif  // _VPLAYER_BUFFER_H
