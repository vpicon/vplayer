// Buffer.h  
//
// Module: player
//
// Definition of the Buffer class.
//


#ifndef _VPLAYER_BUFFER_H
#define _VPLAYER_BUFFER_H


#include <vector>


namespace player {


// Buffer class containing a chunked circular buffer. 
// A thread safe monitor object to read data from input in the 
// producer class, and read data from output in the consumer class, 
// two classes which will run in separate threads.
class Buffer {

    // Represents a circular chunked buffer, stored in the buffer array.
    // Buffer = [Chunk][Chunk] ... [Chunk]
    
public:
    // CONSTRUCTORS AND DESTRUCTORS
    
    // Construcs a new empty buffer object.
    // @param nChunks: > 0, number of chunks in the buffer
    // @param chunkSize: > 0, the size of the inner buffer of each chunk
    // @param minWriteSize: is the minimum size we expect to get for a 
    //        new call to the write position in the buffer.
    //        It must be 0 <= minWriteSize < chunkSize, the greater it is, the more
    //        space is wasted in the chunk. But being 0, we may end up doing calls to the 
    //        buffer where only a few bytes are written.
    // @param dataAlign: data inside the chunk is aligned, intended to be
    //        aligned by the size of PCM frames.
    Buffer(int numChunks, int chunkSize, int minWriteSize, int dataAlign);
    ~Buffer() {}



    // ACCESSORS

    // Gives a Buffer::ReadPosition object to which it can be read some data,
    // the quantity indicated by such ReadPosition object (with the availableData() 
    // method).
    // Buffer::ReadPosition getReadPosition() const;

    // Gives a Buffer::WritePosition object to which it can be written some 
    // data, the quantity indicated by such WritePosition object (with the 
    // availableData() method).
    // Buffer::WritePosition getWritePosition() const;



    // MUTATORS

    // Sets the buffer object to its initial state, all chunks are emptied and 
    // with no data written in it.
    void reset();

    // After reading the stored in the buffer in a ReadPosition object obtained
    // in a call to getReadPosition, the data must be marked as raed by calling
    // the function, in order to get next available data in the buffer.
    void markRead();

    // After writing to the buffer in a WritePosition object obtained in a call 
    // to getReadPosition, the data must be marked as raed by calling the function,
    // in order to get next available data in the buffer.
    void markWritten();

    // CLASS CONSTANTS AND TYPES

    class ReadPosition {};

    class WritePosition {};


private:
    const int _numChunks;  
    const int _chunkSize; 
    const int _minWriteSize; 
    const int _dataAlign; 


    int _writeChunk, _readChunk;   
    
    // thread_mutex _bufferMutex;
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


    class Position {
    public:
        Position(Chunk<_chunkSize> *chunk, int offset, int availableData);

        // Gives the 
        inline int availableData() const { return _availableData; };

         // Converts the position to a char pointer. Useful to use with
         // other functions from low level C libraries (such as in output plugins).
        inline char *toCharPointer();
    private:
        Chunk& _theChunk;    // Current chunk for read or write where data is found
        int _bufferOffset;   // Offset in the current chunk where data is found 
        int _availableData;  // Available data (for reading or writing) 
                             // that was available when the position was obtained
    };


*/






#endif  // _VPLAYER_BUFFER_H
