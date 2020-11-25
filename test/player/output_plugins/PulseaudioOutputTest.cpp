/** 
 * PulseaudioOutputTest.cpp
 *
 * Module: test/player
 *
 * Unit tests of the PulseaudioOutput class.
 *
 */

#include "gtest/gtest.h"
#include "output_plugins/PulseaudioOutput.h"
#include "SampleFormat.h"



namespace {


// HELPER METHODS




// FIXTURE

class PulseaudioOutputTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    
    player::PulseaudioOutput output{};
};



// UNIT TESTS

// TODO: Exception catching tests for open.

/**
 * open() Test Strategy:
 *     Encoding: Signed, Unsigned, Float
 */

// read to an empty buffer
TEST_F(PulseaudioOutputTest, TODO) {
    ASSERT_TRUE(true);
}



}  // namespace 
