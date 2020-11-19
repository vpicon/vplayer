/** 
 * SampleFormatTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the SampleFormat class.
 *
 */

#include "gtest/gtest.h"
#include "SampleFormat.h"

using player::SampleFormat;


namespace {


// HELPER METHODS


// FIXTURE

class SampleFormatTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    
    int frameRate1   = 44100;
    int bitDepth1    = 32;
    int numChannels1 = 1;
    SampleFormat::Endian   end1 = SampleFormat::Endian::little;
    SampleFormat::Encoding enc1 = SampleFormat::Encoding::signedEnc;
    SampleFormat sf1 {frameRate1, bitDepth1, numChannels1, end1, enc1};

    int frameRate2   = 10000;
    int bitDepth2    = 16;
    int numChannels2 = 6;
    SampleFormat::Endian   end2 = SampleFormat::Endian::big;
    SampleFormat::Encoding enc2 = SampleFormat::Encoding::unsignedEnc;
    SampleFormat sf2 {frameRate2, bitDepth2, numChannels2, end2, enc2};

    int frameRate3   = 96000;
    int bitDepth3    = 64;
    int numChannels3 = 2;
    SampleFormat::Endian   end3 = SampleFormat::Endian::little;
    SampleFormat::Encoding enc3 = SampleFormat::Encoding::floatEnc;
    SampleFormat sf3 {frameRate3, bitDepth3, numChannels3, end3, enc3};
};

// UNIT TESTS

/**
 * calculateBitrate() Test
 */

TEST_F(SampleFormatTest, CalculateBitrate) {
    EXPECT_EQ(SampleFormat::calculateBitrate(frameRate1, bitDepth1, numChannels1),
              frameRate1 * bitDepth1 * numChannels1);
    EXPECT_EQ(SampleFormat::calculateBitrate(frameRate2, bitDepth2, numChannels2),
              frameRate2 * bitDepth2 * numChannels2);
    EXPECT_EQ(SampleFormat::calculateBitrate(frameRate3, bitDepth3, numChannels3),
              frameRate3 * bitDepth3 * numChannels3);
}


/**
 * getFrameRate() Test
 */

TEST_F(SampleFormatTest, GetFrameRate) {
    EXPECT_EQ(sf1.getFrameRate(), frameRate1);
    EXPECT_EQ(sf2.getFrameRate(), frameRate2);
    EXPECT_EQ(sf3.getFrameRate(), frameRate3);
}


/**
 * getBitDepth() Test
 */

TEST_F(SampleFormatTest, GetBitDepth) {
    EXPECT_EQ(sf1.getBitDepth(), bitDepth1);
    EXPECT_EQ(sf2.getBitDepth(), bitDepth2);
    EXPECT_EQ(sf3.getBitDepth(), bitDepth3);
}


/**
 * getNumChannels() Test
 */

TEST_F(SampleFormatTest, GetNumChannels) {
    EXPECT_EQ(sf1.getNumChannels(), numChannels1);
    EXPECT_EQ(sf2.getNumChannels(), numChannels2);
    EXPECT_EQ(sf3.getNumChannels(), numChannels3);
}


/**
 * getEndian() Test
 */

TEST_F(SampleFormatTest, GetEndian) {
    EXPECT_EQ(sf1.getEndian(), end1);
    EXPECT_EQ(sf2.getEndian(), end2);
    EXPECT_EQ(sf3.getEndian(), end3);
}


/**
 * getEncoding() Test
 */

TEST_F(SampleFormatTest, GetEncoding) {
    EXPECT_EQ(sf1.getEncoding(), enc1);
    EXPECT_EQ(sf2.getEncoding(), enc2);
    EXPECT_EQ(sf3.getEncoding(), enc3);
}


/**
 * getBitrate() Test
 */

TEST_F(SampleFormatTest, GetBitrate) {
    EXPECT_EQ(sf1.getBitrate(), frameRate1 * bitDepth1 * numChannels1);
    EXPECT_EQ(sf2.getBitrate(), frameRate2 * bitDepth2 * numChannels2);
    EXPECT_EQ(sf3.getBitrate(), frameRate3 * bitDepth3 * numChannels3);
}



}  // namespace 
