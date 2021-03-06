/** 
 * Mp3InputTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the Mp3Input class.
 *
 */

#include "gtest/gtest.h"
#include "input_plugins/Mp3Input.h"
#include "SampleFormat.h"
#include "Buffer.h"

#include <vector>


namespace {


// HELPER METHODS

/** 
 * Given filename, returns local path from current test source dir
 * to the mp3 data given in filename.
 */
std::string dataPath(std::string filename) {
    return "test/data/mp3/" + filename;
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
 * Convert a vector of uint16_t to char.
 */
std::vector<char> shortToCharVec(std::vector<uint16_t> hexvec) {
    std::vector<char> v;
    for (uint16_t x : hexvec) {
        char lsByte = static_cast<char>(x & 0x00ff);  // least significant byte in word
        char msByte = static_cast<char>(x >> 8);  // most significant byte in word
        // Append bytes in LE order
        v.push_back(lsByte);
        v.push_back(msByte);
    }

    return v;
}



// FIXTURE

class Mp3InputTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    static constexpr double durationErrorMargin = 1;  // getDuration tests (in seconds)
    
    size_t numChunks    = 1000; 
    size_t chunkSize    = 2048; 
    size_t minWriteSize = 100; 
    player::Buffer buffer{numChunks, chunkSize, minWriteSize};

    player::SampleFormat::Endian nativeEndian = player::SampleFormat::Endian::little;
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
TEST_F(Mp3InputTest, readEmptyBuffer) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);
    buffer.markWritten(n);

    // Check that we actually read some data
    ASSERT_TRUE(n > 0u);

    // Check the data actually written to the buffer. Should be equal to all 
    // the read data (since buffer initially empty). 
    player::Buffer::Position rPos = buffer.getReadPosition();
    std::vector<char> v = writeToVector(rPos, 0x100);

    // Actual PCM data, obtained with mp3_to_pcm.c program (in test/data/mp3/ dir)
    std::vector<uint16_t> data(0xb0 / 0x10 * 8, 0x0000);
    std::vector<uint16_t> moreData {0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                    0xffff, 0xffff, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};
    for (auto x : moreData) data.push_back(x);

    std::vector<char> actualPCMData = shortToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// read to a full buffer. Should be 0 total read data
TEST_F(Mp3InputTest, readFullBuffer) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Fill buffer
    ASSERT_TRUE(writeToBuffer(buffer, std::vector<char> (numChunks * chunkSize)));

    // Read data form input into buffer
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t n = input.read(wPos);
    buffer.markWritten(n);

    // Test amount of data read. Initially empty buffer, and sufficient data
    // should have read all data available at wPos.
    EXPECT_EQ(n, 0u);
}

// read from position containing no data
TEST_F(Mp3InputTest, readNoData) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Read data form input into buffer
    input.seek(input.getDuration() + 10);  // Go to end of file

    // Try to read data from the file completely read
    player::Buffer::Position wPos = buffer.getWritePosition();
    size_t m = input.read(wPos);
    EXPECT_EQ(m, 0u);
    EXPECT_TRUE(input.reachedEOF());
}



/**
 * seek() Test Strategy:
 *   Current Position: start, middle, end
 *   End Position:     start, middle, end, > end
 */

// seek from start position (0.0) again to start.
TEST_F(Mp3InputTest, seekFromStartToStart) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Seek to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    buffer.markWritten(n);
    ASSERT_TRUE(n > 0u);

    std::vector<char> v = writeToVector(buffer.getReadPosition(), 0x100);

    // Actual PCM data, obtained with mp3_to_pcm.c program (in test/data/mp3/ dir)
    std::vector<uint16_t> data(0xb0 / 0x10 * 8, 0x0000);
    std::vector<uint16_t> moreData {0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                    0xffff, 0xffff, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};
    for (auto x : moreData) data.push_back(x);

    std::vector<char> actualPCMData = shortToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from start position to some middle position.
TEST_F(Mp3InputTest, seekFromMiddleToStart) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Read some data from input
    size_t m = input.read(buffer.getWritePosition());
    buffer.markWritten(m);
    ASSERT_TRUE(m > 0u);

    // Reset buffer
    buffer.reset();

    // Seek back to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    buffer.markWritten(n);
    ASSERT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 0x100);

    // Actual PCM data, obtained with mp3_to_pcm.c program (in test/data/mp3/ dir)
    std::vector<uint16_t> data(0xb0 / 0x10 * 8, 0x0000);
    std::vector<uint16_t> moreData {0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                    0xffff, 0xffff, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};
    for (auto x : moreData) data.push_back(x);

    std::vector<char> actualPCMData = shortToCharVec(data);


    EXPECT_EQ(v, actualPCMData);
}

// seek from end position to start position.
TEST_F(Mp3InputTest, seekFromEndToStart) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Read some data from input
    size_t m;
    while ((m = input.read(buffer.getWritePosition())) != 0)
        /* Do nothing */;
    ASSERT_TRUE(input.reachedEOF());

    // Consume read data
    buffer.reset();

    // Seek back to the initial position
    input.seek(0.0);

    // Read data from the new input position and check it is initial  data
    size_t n = input.read(buffer.getWritePosition());
    buffer.markWritten(n);
    ASSERT_TRUE(n > 0u);
    std::vector<char> v = writeToVector(buffer.getReadPosition(), 0x100);

    // Actual PCM data, obtained with mp3_to_pcm.c program (in test/data/mp3/ dir)
    std::vector<uint16_t> data(0xb0 / 0x10 * 8, 0x0000);
    std::vector<uint16_t> moreData {0x0000, 0xffff, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff, 0xffff,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0001, 0x0001,
                                    0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0xffff, 0xffff,
                                    0xffff, 0xffff, 0x0000, 0x0001, 0x0001, 0x0001, 0x0001, 0x0001};
    for (auto x : moreData) data.push_back(x);

    std::vector<char> actualPCMData = shortToCharVec(data);

    EXPECT_EQ(v, actualPCMData);
}

// seek from start position to some middle position.
TEST_F(Mp3InputTest, seekFromStartToEnd) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Seek back to the initial position
    input.seek(input.getDuration() + 1);

    // Read data from the new input position and check it is initial  data
    EXPECT_TRUE(input.reachedEOF());
}


/**
 * reachedEOF() Test Strategy:
 *    cause: read, seek
 */

// Check we reached eof set when reading
TEST_F(Mp3InputTest, reachedEOFWhileReading) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};
    
    // Check EOF is false
    EXPECT_FALSE(input.reachedEOF());

    // Read whole data from input
    size_t n;
    while ((n = input.read(buffer.getWritePosition())) != 0)
        /* do nothing */;
    EXPECT_TRUE(input.reachedEOF());

    // Go to start again and check eof is false
    input.seek(0.0);
    EXPECT_FALSE(input.reachedEOF());
}

// Check we reached eof set when seeking
TEST_F(Mp3InputTest, reachedEOFWhileSeeking) {
    // Construct Mp3Input Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};
    
    // Check EOF is false
    EXPECT_FALSE(input.reachedEOF());

    // Read some data from input
    input.seek(input.getDuration() + 5);
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

// getSampleFormat test 8 kHz, 16 bit signed, mono
TEST_F(Mp3InputTest, getSampleFormatTest16bitSignedMono) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    16, 
                    1, 
                    nativeEndian,
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 8 kHz, 16 bit signed, stereo
TEST_F(Mp3InputTest, getSampleFormatTest16bitSignedStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("ff-16b-2c-8000hz.mp3");
    player::Mp3Input input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    16, 
                    2, 
                    nativeEndian,
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleFormat test 8 kHz, 16 bit signed, stereo
TEST_F(Mp3InputTest, getSampleFormatTest16bitSigned44kHz) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("ff-16b-2c-44100hz.mp3");
    player::Mp3Input input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    44100, 
                    16, 
                    2, 
                    nativeEndian,
                    player::SampleFormat::Encoding::signedEnc);
}



/**
 * getDuration() Test Strategy:
 *
 *   Duration ~0, >> 0
 *
 * Duration of files, obtained with mediainfo util.
 */

// getDuration
TEST_F(Mp3InputTest, GetDurationTest) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("ff-16b-1c-8000hz.mp3");
    player::Mp3Input input{filename};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 3 * 60 + 7, durationErrorMargin);
}


}  // namespace 
