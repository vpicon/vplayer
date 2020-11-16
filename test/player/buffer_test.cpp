#include "gtest/gtest.h"
#include "buffer.h"

#include <cstdint>


namespace buffer_test {


// HELPER METHODS

/**
 * Writes the given vector to the buffer. Returns true if it could
 * write the entire vector to the buffer, returns false otherwise.
 */
bool writeVectorToBuffer(player::Buffer& buf, std::vector<char> v) {
    size_t n = 0;
    while (n < v.size()) { 
        player::Buffer::Position pos = buf.getWritePosition();
        char *p = pos.toPointer();
        if (pos.size() == 0)  // No space available in the buffer
            return false;

        for (size_t i = 0; i < pos.size(); i++) {
            p[i] = v[i];        
            n++;
        }
    }

    // All the vector was copied 
    return true; 
}


// FIXTURE

class BufferTest : public ::testing::Test {
protected:
    size_t numChunks    = 10;
    size_t chunkSize    = 1000;
    size_t minWriteSize = 100;
    size_t dataAlign    = 50;
    player::Buffer buffer{numChunks, chunkSize, minWriteSize, dataAlign};
};


// TESTS

/**
 * FreeChunks Test Strategy:
 * 
 * free chunks : 0, 1, >1, numChunks
 */

TEST_F(BufferTest, TrivialTest) {
    buffer.reset();

    ASSERT_TRUE(true);
}



}  // namespace buffer_test

