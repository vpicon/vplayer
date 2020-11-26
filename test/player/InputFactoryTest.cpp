/** 
 * SampleFormatTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the SampleFormat class.
 *
 */

#include "gtest/gtest.h"
#include "InputFactory.h"
#include "Input.h"

#include <memory>
#include <string>



namespace {


// HELPER METHODS


// FIXTURE

class InputFactoryTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    std::string simplePath = "/home/Music/";
    std::string dottedPath = "/home/.music/.stored/";
    std::string evilPath   = "/home/.flaca/empty/.wavfiles/";

    std::string wavPath    = "test/data/wav/";

    std::unique_ptr<player::Input> null_unique_ptr{nullptr};
};

// UNIT TESTS

/**
 * getExtension() Test Strategy:
 *    Extension: .wav, .mp3, none
 *    Filename:  contains extension, does not contain extension,
 *               contains dots, contains extensionname without dot,
 *               invalid extension
 */

// Test simple filename containing wav extension.
TEST_F(InputFactoryTest, getExtensionTestSimpleWav) {
    // Create filename and expected result
    std::string filename  = simplePath + "song.wav";
    std::string extension = "wav";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test simple filename containing mp3 extension.
TEST_F(InputFactoryTest, getExtensionTestSimpleMp3) {
    // Create filename and expected result
    std::string filename  = simplePath + "song.mp3";
    std::string extension = "mp3";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test simple filename containing no extension.
TEST_F(InputFactoryTest, getExtensionTestNoExtension) {
    // Create filename and expected result
    std::string filename  = simplePath + "song";
    std::string extension = "";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test simple filename containing a not supported extension.
TEST_F(InputFactoryTest, getExtensionTestNotSupportedExtension) {
    // Create filename and expected result
    std::string filename  = simplePath + "song.jpeg";
    std::string extension = "";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test simple filename containing invalid extension without dot.
TEST_F(InputFactoryTest, getExtensionTestInvalidExtensionWithoutDot) {
    // Create filename and expected result
    std::string filename  = simplePath + "songwav";
    std::string extension = "";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test filename containing extra dots in the filename.
TEST_F(InputFactoryTest, getExtensionTestPathWithExtraDots) {
    // Create filename and expected result
    std::string filename  = dottedPath + "song.wav";
    std::string extension = "wav";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test filename containing a path with an "extension in the middle" no extension.
TEST_F(InputFactoryTest, getExtensionTestInvalidExtensionInMiddleNoExt) {
    // Create filename and expected result
    std::string filename  = evilPath + "song";
    std::string extension = "";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}

// Test filename containing a path with an "extension in the middle" with a valid extension at end.
TEST_F(InputFactoryTest, getExtensionTestInvalidExtensionInMiddleWithExt) {
    // Create filename and expected result
    std::string filename  = evilPath + "song.mp3";
    std::string extension = "mp3";

    // Test obtained results
    EXPECT_EQ(player::InputFactory::getExtension(filename), extension);
}



/**
 * create() Test Strategy:
 *    filename: valid filename, not valid input. 
 *    TODO: catch exception strategy
 */

// Test simple filename containing wav extension.
TEST_F(InputFactoryTest, createTestWavFile) {
    // Create filename and expected result
    std::string filename  = wavPath + "M1F1-int32-AFsp.wav";
    auto input = player::InputFactory::create(filename);

    // Test obtained results
    ASSERT_NE(input, null_unique_ptr);
    // TODO: check input is of type WavInput
}




}  // namespace 
