/** 
 * BufferTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the Buffer class.
 *
 */

#include "gtest/gtest.h"
#include "Buffer.h"

#include <cstdint>
#include <chrono>
#include <vector>
#include <thread>


namespace {


// HELPER METHODS

/**
 * Writes the given vector to the buffer. Returns true if it could
 * write the entire vector to the buffer, returns false otherwise.
 */
bool writeVectorToBuffer(player::Buffer& buf, std::vector<char> data) {
    size_t n = 0;
    while (n < data.size()) { 
        player::Buffer::Position pos = buf.getWritePosition();
        if (pos.size() == 0)  // No space available in the buffer
            return false;

        char *p = pos.toPointer();
        size_t i = 0;
        while (i < pos.size() && (i+n) < data.size()) {
            p[i] = data[n + i];
            i++;
        }
        n += i;
        buf.markWritten(i);
    }

    // All the vector was copied 
    return true; 
}

/**
 * Tests if the given buffer is at clean empty state
 */
void testEmptyBuffer(player::Buffer& buf, size_t chunkSize) {
    EXPECT_EQ(buf.getReadPosition().size(), 0u);
    EXPECT_EQ(buf.getWritePosition().size(), chunkSize);
    EXPECT_EQ(buf.filledChunks(), 0u);
}


/**
 * A Producer function which writes the in_data to the given buffer.
 * The function may send to sleep for some time the running process 
 * if it finds the buffer full.
 */
void producer(player::Buffer& buf, const std::vector<char>& inData) {
    size_t n = 0;  // inData position index
    while (n < inData.size()) {
        // Get Write and check there is available space in it
        player::Buffer::Position wPos = buf.getWritePosition();        
        if (wPos.size() == 0u) {  // Wait for the buffer to empty
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
            return;
            // TODO: continue
        }

        // Write wPos.size() bytes from inData to the buffer
        char *p = wPos.toPointer();
        size_t i = 0;
        while (i < wPos.size() && (i+n) < inData.size()) {
            p[i] = inData[n + i];
            i++;
        }
        n += i;
        buf.markWritten(i);
    }
}

/**
 * A Producer function which writes to out_data from the given buffer.
 * The function may send to sleep for some time the running process 
 * if it finds the buffer full.
 * It assumes that out_data will have the exact size of the data in the buffer.
 */
void consumer(player::Buffer& buf, const std::vector<char>& outData) {
    size_t n = 0;  // outData position index
    while (n < outData.size()) {
        // Get Write and check there is available space in it
        player::Buffer::Position rPos = buf.getReadPosition();        
        if (rPos.size() == 0u) {  // Wait for the buffer to empty
            std::this_thread::sleep_for(std::chrono::milliseconds {1});
            return;
            // TODO: continue
        }

        // Write wPos.size() bytes from in_data to the buffer
        char *p = rPos.toPointer();
        size_t i = 0;
        while (i < rPos.size() && (i+n) < outData.size()) {
            p[i] = outData[n + i];
            i++;
        }
        n += i;
        buf.markRead(i);
    }
}


/**
 * Given a Position obtained from getReadPosition, compares that the data
 * stored in such position is equal to the data in the given vector. 
 * Returns false if they differ in any byte, true otherwise.
 * It is assumed that there are at least data.size() bytes available in
 * the given read position.
 */
bool compareReadData(player::Buffer::Position readPos, 
                     std::vector<char> data) 
{
    char *p = readPos.toPointer();  // pointer to the data
    for (size_t i = 0; i < data.size(); i++) {
        if (p[i] != data[i])
            return false;
    }

    return true;
}


// FIXTURE

class BufferTest : public testing::Test {
protected:
    void SetUp() override {
        std::vector<char> data(numChunks * chunkSize, 'a');
        writeVectorToBuffer(fullBuffer, data);
    }

    // No TearDown() needed

    size_t numChunks    = 10;
    size_t chunkSize    = 1000;
    size_t minWriteSize = 100;

    player::Buffer emptyBuffer{numChunks, chunkSize, minWriteSize};
    player::Buffer fullBuffer{numChunks, chunkSize, minWriteSize};
};


// UNIT TESTS


/**
 * getReadPosition() Test Strategy:
 *
 *   Buffer State: empty, full, non-empty
 *   Position.size(): chunkSize, <chunkSize, 0
 *
 */

// getReadPosition from empty buffer
TEST_F(BufferTest, GetReadPositionEmptyBuffer) {
    player::Buffer::Position pos = emptyBuffer.getReadPosition();

    // Buffer is initially empty
    EXPECT_EQ(pos.toPointer(), nullptr);
    EXPECT_EQ(pos.size(), 0u);
}

// getReadPosition from buffer with one partially written chunk
TEST_F(BufferTest, GetReadPositionPartiallyFilledChunk) {
    size_t n = chunkSize/2;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    player::Buffer::Position pos = emptyBuffer.getReadPosition();

    // There should be n data to read
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_EQ(pos.size(), n);
    EXPECT_TRUE(compareReadData(pos, data));
}

// getReadPosition from buffer with filled chunks
TEST_F(BufferTest, GetReadPositionSomeFilledChunks) {
    size_t n = 2 * chunkSize;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    player::Buffer::Position pos = emptyBuffer.getReadPosition();

    // There should be at most chunkSize data to read
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() <= chunkSize);
    EXPECT_TRUE(compareReadData(pos, std::vector<char>(pos.size(), 'a')));
}

// getReadPosition from buffer with full buffer
TEST_F(BufferTest, GetReadPositionFullBuffer) {
    player::Buffer::Position pos = fullBuffer.getReadPosition();

    // There should be at most chunkSize data to read
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() <= chunkSize);
}



/**
 * getWritePosition() Test Strategy:
 *
 *   Buffer State: empty, full, non-empty
 *   Position.size(): chunkSize, < chunkSize, 0
 *
 */

// getWritePosition from empty buffer 
TEST_F(BufferTest, GetWritePositionEmptyBuffer) {
    player::Buffer::Position pos = emptyBuffer.getWritePosition();

    // There should be entire chunk to write
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() == chunkSize);
}

// getWritePosition from buffer with one partially written chunk
TEST_F(BufferTest, GetWritePositionPartiallyFilledChunk) {
    size_t n = chunkSize/2;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    player::Buffer::Position pos = emptyBuffer.getWritePosition();

    // There should be half chunk to write
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() == chunkSize/2);
}

// getWritePosition from buffer with one almost filled chunk
TEST_F(BufferTest, GetWritePositionAlmostFilledChunk) {
    size_t n = chunkSize - 1;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    player::Buffer::Position pos = emptyBuffer.getWritePosition();

    // There should be at least minWriteSize space to write
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() >= minWriteSize);
}

// getWritePosition from buffer with filled chunks
TEST_F(BufferTest, GetWritePositionSomeFilledChunks) {
    size_t n = 2 * chunkSize;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    player::Buffer::Position pos = emptyBuffer.getWritePosition();

    // There should be at least minWriteSize space to write
    EXPECT_NE(pos.toPointer(), nullptr);
    EXPECT_TRUE(pos.size() <= chunkSize);
    EXPECT_TRUE(pos.size() >= minWriteSize);
}

// getWritePosition from buffer with full buffer
TEST_F(BufferTest, GetWritePositionFullBuffer) {
    player::Buffer::Position pos = fullBuffer.getWritePosition();

    // There should be no space to write
    EXPECT_EQ(pos.toPointer(), nullptr);
    EXPECT_EQ(pos.size(), 0u);
}



/**
 * filledChunks() Test Strategy:
 * 
 *   full chunks: 0, 1, >1, numChunks
 */

// filledChunks with empty buffer
TEST_F(BufferTest, FilledChunksEmptyBuffer) {
    EXPECT_EQ(emptyBuffer.filledChunks(), 0u);
}

// filledChunks with partially filled chunk 
TEST_F(BufferTest, FilledChunksPartiallyFilledChunk) {
    size_t n = chunkSize/2;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    // There should be no chunk full
    EXPECT_EQ(emptyBuffer.filledChunks(), 0u);
}

// filledChunks with one full chunk 
TEST_F(BufferTest, FilledChunksFullChunk) {
    size_t n = chunkSize;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    // There should be no chunk full
    EXPECT_EQ(emptyBuffer.filledChunks(), 1u);
}

// filledChunks with two full chunk 
TEST_F(BufferTest, FilledChunksTwoFullChunks) {
    size_t n = 2 * chunkSize;
    std::vector<char> data(n, 'a');

    // Should be able to write 
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    // There should be no chunk full
    EXPECT_EQ(emptyBuffer.filledChunks(), 2u);
}

// filledChunks with full buffer 
TEST_F(BufferTest, FilledChunksFullBuffer) {
    // There should be no chunk full
    EXPECT_EQ(fullBuffer.filledChunks(), numChunks);
}



/**
 * reset() Test Strategy:
 * 
 *   buffer prior state: empty, one full chunk, some chunks half filled, full 
 */

// reset with empty buffer
TEST_F(BufferTest, ResetEmptyBuffer) {
    // Reset the buffer
    emptyBuffer.reset();
        
    // Check 
    testEmptyBuffer(emptyBuffer, chunkSize);
}

// reset with filled chunk
TEST_F(BufferTest, ResetFilledChunk) {
    size_t n = chunkSize;
    std::vector<char> data(n, 'a');

    // Should be able to write data
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    // Reset the buffer
    emptyBuffer.reset();
        
    // Check 
    testEmptyBuffer(emptyBuffer, chunkSize);
}

// reset with multiple filled chunks
TEST_F(BufferTest, ResetMultipleFilledChunks) {
    size_t n = 3*chunkSize + chunkSize/2;
    std::vector<char> data(n, 'a');

    // Should be able to write data
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));
            
    // Reset the buffer
    emptyBuffer.reset();
        
    // Check 
    testEmptyBuffer(emptyBuffer, chunkSize);
}

// reset with full buffer
TEST_F(BufferTest, ResetFullBuffer) {
    // Reset the buffer
    fullBuffer.reset();
        
    // Check 
    testEmptyBuffer(fullBuffer, chunkSize);
}


/**
 * markRead() Test Strategy:
 * 
 *   amount read: 0, 1, < all available, all available
 */

// markRead no data
TEST_F(BufferTest, MarkReadNoData) {
    size_t nWrite = 100;
    std::vector<char> data(nWrite, 'a');

    // Write nWrite bytes into buffer
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));

    // Read 0 bytes
    player::Buffer::Position oldPos = emptyBuffer.getReadPosition();
    ASSERT_EQ(oldPos.size(), nWrite);

    emptyBuffer.markRead(0u);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), nWrite);
}

// markRead with a few bytes
TEST_F(BufferTest, MarkReadSingleByte) {
    size_t nWrite = 100, nRead = 1;
    std::vector<char> data(nWrite, 'a');

    // Write nWrite bytes into buffer
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));

    // Read nRead bytes
    player::Buffer::Position oldPos = emptyBuffer.getReadPosition();
    ASSERT_EQ(oldPos.size(), nWrite);

    emptyBuffer.markRead(nRead);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), nWrite - nRead);
}

// markRead with all available data
TEST_F(BufferTest, MarkReadEntireData) {
    size_t nWrite = chunkSize;
    size_t nRead = nWrite;
    std::vector<char> data(nWrite, 'a');

    // Write nWrite bytes into buffer
    ASSERT_TRUE(writeVectorToBuffer(emptyBuffer, data));

    // Read nRead bytes
    player::Buffer::Position oldPos = emptyBuffer.getReadPosition();
    ASSERT_EQ(oldPos.size(), nWrite);

    emptyBuffer.markRead(nRead);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), 0u);
}



/**
 * markWrite() Test Strategy:
 * 
 *   amount writen: 0, 1, < all available, all available
 */

// markWrite no data
TEST_F(BufferTest, MarkWriteNoData) {
    // Write 0 bytes
    player::Buffer::Position wPos = emptyBuffer.getWritePosition();
    ASSERT_NE(wPos.size(), 0u);

    emptyBuffer.markWritten(0u);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), 0u);
}

// markWrite with a few bytes
TEST_F(BufferTest, MarkWriteSingleByte) {
    size_t nWrite = 1;

    // Read nRead bytes
    player::Buffer::Position wPos = emptyBuffer.getWritePosition();
    ASSERT_NE(wPos.size(), 0u);

    emptyBuffer.markWritten(nWrite);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), nWrite);
}

// markWrite with all available data
TEST_F(BufferTest, MarkWriteEntireData) {
    // Read nRead bytes
    player::Buffer::Position wPos = emptyBuffer.getWritePosition();
    ASSERT_NE(wPos.size(), 0u);
    size_t nWrite = wPos.size();

    emptyBuffer.markWritten(nWrite);

    // Check new Position to read contains less data
    player::Buffer::Position pos = emptyBuffer.getReadPosition();
    EXPECT_EQ(pos.size(), nWrite);
}

/**
 * Synchronized Tests: 
 * Tests that the Buffer object is thread safe, appropiate to use in
 * a consumer producer threaded scenario. Test Cases:
 *   data size: 1, >1, chunkSize, bufferSize, > bufferSize
 *   Synchronization: sequential (first producer, then consumer)
 *                    concurrent
 */

// Sequential message sending a single byte
TEST_F(BufferTest, ProducerConsumerSequentialSingleByte) {
    // Produce input data and send it to buffer
    size_t n = 1;
    std::vector<char> inData(n, 'a');
    producer(emptyBuffer, inData);

    // Receive data from buffer
    std::vector<char> outData(n);
    consumer(emptyBuffer, outData);

    // Compare input and output data
    EXPECT_TRUE(inData == outData);
}

// Sequential message sending a several chunks of message
TEST_F(BufferTest, ProducerConsumerSequentialSeveralChunks) {
    // Produce input data and send it to buffer
    size_t n = 2 * chunkSize;
    std::vector<char> inData(n, 'a');
    inData[chunkSize/2] = 'c';  // Random modifications
    producer(emptyBuffer, inData);

    // Receive data from buffer
    std::vector<char> outData(n);
    consumer(emptyBuffer, outData);

    // Compare input and output data
    EXPECT_TRUE(inData == outData);
}

// Concurrent message sending, entire buffer
TEST_F(BufferTest, ProducerConsumerConcurrentBufferSize) {
    // Produce input data and send it to buffer in a thread
    size_t n = numChunks * chunkSize;
    std::vector<char> inData(n, 'a');
    producer(emptyBuffer, inData);
    std::thread producerThread {producer, 
                                std::ref(emptyBuffer),
                                std::ref(inData)};

    // Receive data from buffer in a thread
    std::vector<char> outData(n);
    consumer(emptyBuffer, outData);
    std::thread consumerThread {consumer, 
                                std::ref(emptyBuffer), 
                                std::ref(outData)};

    // Wait for threads to terminate
    producerThread.join();
    consumerThread.join();

    // Compare input and output data
    EXPECT_TRUE(inData == outData);
}

// Concurrent message sending, data size greater than buffer
TEST_F(BufferTest, ProducerConsumerConcurrentMoreDataThanBuffer) {
    // Produce input data and send it to buffer in a thread
    size_t n = 10 * numChunks * chunkSize;
    std::vector<char> inData(n, 'a');
    producer(emptyBuffer, inData);
    std::thread producerThread {producer, 
                                std::ref(emptyBuffer), 
                                std::ref(inData)};

    // Receive data from buffer in a thread
    std::vector<char> outData(n);
    consumer(emptyBuffer, outData);
    std::thread consumerThread {consumer, 
                                std::ref(emptyBuffer), 
                                std::ref(outData)};

    // Wait for threads to terminate
    producerThread.join();
    consumerThread.join();

    // Compare input and output data
    EXPECT_TRUE(inData == outData);
}



}  // namespace buffer_test
