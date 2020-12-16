/** 
 * ArtistTest.cpp
 *
 * Module: test/database
 *
 * Unit tests of the Artist class.
 *
 */

#include "gtest/gtest.h"
#include "Artist.h"

#include <string>


namespace {


// HELPER METHODS


// FIXTURE

class ArtistTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    // Generate a new artist
    int id {10};
    std::string name {"Victor"};
    std::string imgSource {"/home/usr/some_image.jpg"};
    std::string bio {"A nice person."};

    database::Artist artist {id, name, imgSource, bio};

    // Generate a default constructor empty artist
    database::Artist emptyArtist {};
};

// UNIT TESTS

/**
 * Test getters
 */

TEST_F(ArtistTest, getters) {
    EXPECT_EQ(artist.getId(), id);
    EXPECT_EQ(artist.getName(), name);
    EXPECT_EQ(artist.getImgSource(), imgSource);
    EXPECT_EQ(artist.getBio(), bio);
}


/**
 * Test default constructor
 */
TEST_F(ArtistTest, defaultConstructor) {
    EXPECT_EQ(emptyArtist.getId(), 0);
    EXPECT_EQ(emptyArtist.getName(), "");
    EXPECT_EQ(emptyArtist.getImgSource(), "");
    EXPECT_EQ(emptyArtist.getBio(), "");
}


/**
 * Test setters
 */

TEST_F(ArtistTest, setters) {
    // Define new values
    int newId {13};
    std::string newName {"Victor"};
    std::string newImgSource {"/home/usr/some_image.jpg"};
    std::string newBio {"A nice person."};

    // Set new values
    artist.setId(newId);
    artist.setName(newName);
    artist.setImgSource(newImgSource);
    artist.setBio(newBio);

    // Test new values
    EXPECT_EQ(artist.getId(), newId);
    EXPECT_EQ(artist.getName(), newName);
    EXPECT_EQ(artist.getImgSource(), newImgSource);
    EXPECT_EQ(artist.getBio(), newBio);
}



}  // namespace
