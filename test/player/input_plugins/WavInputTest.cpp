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

namespace {


// HELPER METHODS

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
    static constexpr double durationErrorMargin = 0.1;  // seconds
};


// UNIT TESTS

/**
 * getSampleSpecs() Test Strategy:
 *
 *   Channels: 1, 2 (> 2 not supported)
 *   FrameRate: 44100, != 44100 samples per sec
 *   BitDepth: 16, 24, 32, 64
 *   Encoding: Float, Unsigned/Signed Int
 *   Endiannes: Little in all of them
 */

// getSampleSpecs test 8 kHz, 8bit unsigned, stereo
TEST_F(WavInputTest, GetSampleSpecsTest8bitUnsigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-uint8-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    8, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::unsignedEnc);
}

// getSampleSpecs test 8 kHz, 16bit signed, stereo
TEST_F(WavInputTest, GetSampleSpecsTest16bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int16-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    16, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleSpecs test 8 kHz, 24bit signed, stereo
TEST_F(WavInputTest, GetSampleSpecsTest24bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int24-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    24, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleSpecs test 8 kHz, 32bit signed, stereo
TEST_F(WavInputTest, GetSampleSpecsTest32bitSigned) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int32-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    32, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleSpecs test 8 kHz, 32bit float, stereo
TEST_F(WavInputTest, GetSampleSpecsTest32bitFloat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float32-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    32, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::floatEnc);
}

// getSampleSpecs test 8 kHz, 64bit float, stereo
TEST_F(WavInputTest, GetSampleSpecsTest64bitFloat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float64-AFsp.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    8000, 
                    64, 
                    2, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::floatEnc);
}

// getSampleSpecs test 22.05 kHz, 24bit signed, mono
TEST_F(WavInputTest, GetSampleSpecsTest22kHzMonoExtensibleFormat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm2422m.wav");
    player::WavInput input{filename};


    // Test Sample Format were correctly obtained
    testSampleSpecs(input.getSampleFormat(),
                    22050, 
                    24, 
                    1, 
                    player::SampleFormat::Endian::little, 
                    player::SampleFormat::Encoding::signedEnc);
}

// getSampleSpecs test 44.1 kHz, 24bit signed, mono
TEST_F(WavInputTest, GetSampleSpecsTestMono44kHzMonoExtensibleFormat) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm4410024bitmono.wav");
    player::WavInput input{filename};


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
    player::WavInput input{filename};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration signed, 8 kHz, stereo
TEST_F(WavInputTest, GetDurationTestSignedStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-int24-AFsp.wav");
    player::WavInput input{filename};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration float, 8 kHz, stereo
TEST_F(WavInputTest, GetDurationTestFloatStereo) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("M1F1-float32-AFsp.wav");
    player::WavInput input{filename};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 2.9, durationErrorMargin);
}

// getDuration signed, 44.1 kHz, mono, small duration
TEST_F(WavInputTest, GetDurationTest44kHzMonoSmall) {
    // Construct WavInput Object and get its Format Specs
    std::string filename = dataPath("pcm4410024bitmono.wav");
    player::WavInput input{filename};

    // Test the duration of input
    EXPECT_NEAR(input.getDuration(), 0.1, durationErrorMargin);
}



}  // namespace 
