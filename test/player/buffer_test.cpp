#include "gtest/gtest.h"

#include "buffer.h"

namespace buffer_test {

    // Fixture
    class BufferTest : public ::testing::Test {
    protected:
        int numChunks    = 10;
        int chunkSize    = 1000;
        int minWriteSize = 100;
        int dataAlign    = 50;
        Buffer buffer{numChunks, chunkSize, minWriteSize, dataAlign};
    };


    TEST_F(BufferTest, TrivialTest) {
        buffer.reset();

        ASSERT_TRUE(true);
    }
}

