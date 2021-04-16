/** 
 * TracklistTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the Tracklist class.
 *
 */

#include "gtest/gtest.h"
#include "Tracklist.h"



namespace {


// HELPER METHODS


// FIXTURE

class TracklistTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

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
TEST_F(TracklistTest, TODO) {
    // Test obtained results
    EXPECT_TRUE(false);
}


}  // namespace 
