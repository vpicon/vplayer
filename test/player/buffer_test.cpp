#include "gtest/gtest.h"
#include "buffer.h"

#include <cstdint>
#include <vector>


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
        for (size_t i = 0; i < pos.size(); i++) {
            p[i] = data[i];        
            n++;
        }
        buf.markWritten(pos.size());
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
 * Given a Position obtained from getReadPosition, compares that the data
 * stored in such position is equal to the data in the given vector. 
 * Returns false if they differ in any byte, true otherwise.
 * It is assumed that there are at least data.size() bytes available in
 * the given read position.
 */
bool compareReadData(player::Buffer::Position readPos, 
                     std::vector<char> data) {
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
    size_t dataAlign    = 50;
    player::Buffer emptyBuffer{numChunks, chunkSize, minWriteSize, dataAlign};

    player::Buffer fullBuffer{numChunks, chunkSize, minWriteSize, dataAlign};
};


// TESTS


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
 *   Position.size(): chunkSize, <chunkSize, 0
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




}  // namespace buffer_test

