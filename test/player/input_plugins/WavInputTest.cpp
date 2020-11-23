/** 
 * BufferTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the Buffer class.
 *
 */

#include "gtest/gtest.h"
#include "input_plugins/WavInput.h"
#include "SampleFormat.h"
#include "Buffer.h"

#include <vector>


namespace {


// HELPER METHODS


/**
 * Return a vector of size n, of n bytes read from pos, where n < pos.size()
 */
bool writeToBuffer(player::Buffer& buf, const std::vector<char>& data) {
    size_t n = 0;
    while (n < data.size()) {
        player::Buffer::Position wPos = buf.getWritePosition();
        if (wPos.size() == 0)
            return false;

        char *p = wPos.toPointer();
        size_t i = 0;
        while (i < wPos.size() && (i + n) < data.size()) {
            p[i] = data[n + i];
            i++;
        }
        n += i;
        buf.markWritten(i);
    }

    return true;
}

/**
 * Return a vector of size n, of n bytes read from pos, where n < pos.size()
 */
std::vector<char> writeToVector(player::Buffer::Position pos, size_t n) {
    std::vector<char> v(n);
    char *p = pos.toPointer();
    for (size_t i = 0; i < n; i++) 
        v[i] = p[i]; 
      
    return v;
}

/**
 * Convert a vector of uint8_t to char.
 */
std::vector<char> hexToCharVec(std::vector<uint8_t> hexvec) {
    std::vector<char> v;
    for (uint8_t x : hexvec)
        v.push_back(static_cast<char>(x));

    return v;
}

/** 
 * Given filename, returns local path from current test source dir
 * to the WAV data given in filename.
 */
std::string dataPath(std::string filename) {
    return "test/data/wav/" + filename;
}


void testSampleSpecs(const player::SampleFormat& sf,
                     int frameRate,
                     int bitDepth, 
                     int numChannels,
                     player::SampleFormat::Endian end,
                     player::SampleFormat::Encoding enc)
{ 
    EXPECT_EQ(sf.getFrameRate(),   frameRate);
    EXPECT_EQ(sf.getBitDepth(),    bitDepth);
    EXPECT_EQ(sf.getNumChannels(), numChannels);  
    EXPECT_EQ(sf.getEndian(),      end);
    EXPECT_EQ(sf.getEncoding(),    enc);
}



// FIXTURE

class WavInputTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    static constexpr double durationErrorMargin = 0.1;  // getDuration tests
    
    size_t numChunks    = 100; 
    size_t chunkSize    = 1000; 
    size_t minWriteSize = 100; 
    player::Buffer buffer{numChunks, chunkSize, minWriteSize};
};



// UNIT TESTS

// TODO: Exception catching tests for invalid constructors

/**
 * read() Test Strategy:
 *   Buffer state: empty, full, non-empty chunk
 *   Input data: no data (EOF), more data than space at buffer position,
 *               less data than space at buffer position.
 */

// read to an empty buffer
TEST_F(WavInputTest, readEmptyBuffer) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);

    // Test amount of data read. Initially empty buffer, and sufficient data
    // should have read all data available at wPos.
    EXPECT_EQ(n, wPos.size());

    // Check the data actually written to the buffer. Should be equal to all 
    // the read data (since buffer initially empty). 
    // Read 16 first bytes of the buffer into a vector.
    player::Buffer::Position rPos = buffer.getReadPosition();
    ASSERT_EQ(n, rPos.size()); 
    std::vector<char> v = writeToVector(rPos, 16);

    // Actual PCM data, obtained with hexdump (first 16 bytes of PCMdata)
    std::vector<uint8_t> data {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x01, 0x00, 0x02, 0x00, 0xfd, 0xff, 0x00, 0x00};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// read to a full buffer. Should be 0 total read data
TEST_F(WavInputTest, readFullBuffer) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Fill buffer
    ASSERT_TRUE(writeToBuffer(buffer, std::vector<char> (numChunks * chunkSize)));

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);

    // Test amount of data read. Initially empty buffer, and sufficient data
    // should have read all data available at wPos.
    EXPECT_EQ(n, 0u);
}

// read less data from input than space of buffer
TEST_F(WavInputTest, readLessDataThanBufferSize) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);

    // Test amount of data read. Initially empty buffer, and sufficient data
    // should have read all data available at wPos.
    EXPECT_TRUE(n < wPos.size());

    // Check the data actually written to the buffer. Should be equal to all 
    // the read data (since buffer initially empty). 
    // Read 16 first bytes of the buffer into a vector.
    player::Buffer::Position rPos = buffer.getReadPosition();
    ASSERT_EQ(n, rPos.size()); 
    std::vector<char> v = writeToVector(rPos, 8);

    // Actual PCM data, obtained with hexdump (the 8 bytes of PCMdata)
    std::vector<uint8_t> data {0x00, 0xfb, 0x0c, 0x83, 0x1f, 0x0c, 0x0d, 0xc8};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// read from position containing no data
TEST_F(WavInputTest, readNoData) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);
    EXPECT_TRUE(n < wPos.size());

    // Try to read data from the file completely read
    player::Buffer::Position wPos2 = buffer.getWritePosition();
    size_t m = input.read(wPos2);
    EXPECT_EQ(m, 0u);
    EXPECT_TRUE(input.reachedEOF());
}



/**
 * seek() Test Strategy:
 *   Current Position: start, middle, end
 *   End Position:     start, middle, end, > end
 */

// seek from start position (0.0) again to start.
TEST_F(WavInputTest, seekFromStartToStart) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Seek to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    ASSERT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 16);

    // PCM data, obtained with hexdump (first 16 bytes of PCMdata)
    std::vector<uint8_t> data {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x01, 0x00, 0x02, 0x00, 0xfd, 0xff, 0x00, 0x00};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from start position to some middle position.
TEST_F(WavInputTest, seekFromMiddleToStart) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Read some data from input
    size_t m = input.read(buffer.getWritePosition());
    ASSERT_TRUE(m > 0u);

    // Consume read data
    buffer.markRead(buffer.getReadPosition().size());

    // Seek back to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    ASSERT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 16);

    // PCM data, obtained with hexdump (first 16 bytes of PCMdata)
    std::vector<uint8_t> data {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                               0x01, 0x00, 0x02, 0x00, 0xfd, 0xff, 0x00, 0x00};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from end position to start position.
TEST_F(WavInputTest, seekFromEndToStart) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};

    // Read some data from input
    size_t m = input.read(buffer.getWritePosition());
    ASSERT_TRUE(m > 0u);
    ASSERT_TRUE(input.reachedEOF());

    // Consume read data
    buffer.markRead(buffer.getReadPosition().size());

    // Seek back to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    ASSERT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 8);

    // PCM data, obtained with hexdump (first 16 bytes of PCMdata)
    std::vector<uint8_t> data {0x00, 0xfb, 0x0c, 0x83, 0x1f, 0x0c, 0x0d, 0xc8};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from start position to some middle position.
TEST_F(WavInputTest, seekFromStartToMiddle) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testOneFrameSecond.wav");
    player::WavInput input{filename, buffer};

    // Seek back to the initial position
    input.seek(2.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    EXPECT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 4);

    // PCM data, obtained with hexdump 
    std::vector<uint8_t> data {0x05, 0x06, 0x07, 0x08};
    std::vector<char> actualPCMData = hexToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from start position to some middle position.
TEST_F(WavInputTest, seekFromStartToEnd) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int32-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Seek back to the initial position
    input.seek(input.getDuration() + 1);

    // Read data from the new input position and check it is initial  data
    EXPECT_TRUE(input.reachedEOF());
}



/**
 * reachedEOF() Test Strategy:
 */

// Check we reached eof set when reading
TEST_F(WavInputTest, reachedEOFWhileReading) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};
    
    // Check EOF is false
    EXPECT_FALSE(input.reachedEOF());

    // Read some data from input
    input.read(buffer.getWritePosition());
    EXPECT_TRUE(input.reachedEOF());

    // Go to start again and check eof is false
    input.seek(0.0);
    EXPECT_FALSE(input.reachedEOF());
}

// Check we reached eof set when seeking
TEST_F(WavInputTest, reachedEOFWhileSeeking) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};
    
    // Check EOF is false
    EXPECT_FALSE(input.reachedEOF());

    // Read some data from input
    input.seek(input.getDuration() + 1);
    EXPECT_TRUE(input.reachedEOF());
}


/**
 * getSampleFormat() Test Strategy:
 *
 *   Channels: 1, 2 (> 2 not supported)
 *   FrameRate: 44100, != 44100 samples per sec
 *   BitDepth: 16, 24, 32, 64
 *   Encoding: Float, Unsigned/Signed Int
 *   Endiannes: Little in all of them
 */

// getSampleFormat test 8 kHz, 8bit unsigned, stereo
TEST_F(WavInputTest, getSampleFormatTest8bitUnsigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-uint8-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    8, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::unsignedEnc);
}

// getSampleFormat test 8 kHz, 16bit signed, stereo
TEST_F(WavInputTest, getSampleFormatTest16bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    16, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 8 kHz, 24bit signed, stereo
TEST_F(WavInputTest, getSampleFormatTest24bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int24-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    24, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 8 kHz, 32bit signed, stereo
TEST_F(WavInputTest, getSampleFormatTest32bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int32-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    32, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 8 kHz, 32bit float, stereo
TEST_F(WavInputTest, getSampleFormatTest32bitFloat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float32-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    32, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::floatEnc);
}

// getSampleFormat test 8 kHz, 64bit float, stereo
TEST_F(WavInputTest, getSampleFormatTest64bitFloat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float64-AFsp.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    64, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::floatEnc);
}

// getSampleFormat test 22.05 kHz, 24bit signed, mono
TEST_F(WavInputTest, getSampleFormatTest22kHzMonoExtensibleFormat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm2422m.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    22050, 
                    24, 
                    1, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 44.1 kHz, 24bit signed, mono
TEST_F(WavInputTest, getSampleFormatTestMono44kHzMonoExtensibleFormat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm4410024bitmono.wav");
    player::WavInput input{filename, buffer};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    44100, 
                    24, 
                    1, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}



/**
 * getDuration() Test Strategy:
 *
 *   Duration ~0, >> 0
 *   Channels: 1, 2 (> 2 not supported)
 *   FrameRate: 44100, != 44100 samples per sec
 *   Encoding: Float, Unsigned/Signed Int
 *
 * Duration of files, obtained with mediainfo util.
 */

// getDuration Unsigned, 8 kHz, stereo
TEST_F(WavInputTest, GetDurationTestUnsignedStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-uint8-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration signed, 8 kHz, stereo
TEST_F(WavInputTest, GetDurationTestSignedStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int24-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration float, 8 kHz, stereo
TEST_F(WavInputTest, GetDurationTestFloatStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float32-AFsp.wav");
    player::WavInput input{filename, buffer};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration signed, 44.1 kHz, mono
TEST_F(WavInputTest, GetDurationTest44kHzMono) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm4410024bitmono.wav");
    player::WavInput input{filename, buffer};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 0.1, durationErrorMargin);
}

// getDuration signed, 44.1 kHz, mono
TEST_F(WavInputTest, GetDurationTestSmall) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("testShort.wav");
    player::WavInput input{filename, buffer};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 0.0, durationErrorMargin);
}



}  // namespace 
