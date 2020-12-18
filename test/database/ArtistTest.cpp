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

TEST_F(ArtistTest, Getters) {
    EXPECT_EQ(artist.getId(), id);
    EXPECT_EQ(artist.getName(), name);
    EXPECT_EQ(artist.getImgSource(), imgSource);
    EXPECT_EQ(artist.getBio(), bio);
}


/**
 * Constructors Test
 */

TEST_F(ArtistTest, DefaultConstructor) {
    EXPECT_EQ(emptyArtist.getId(), 0);
    EXPECT_EQ(emptyArtist.getName(), "");
    EXPECT_EQ(emptyArtist.getImgSource(), "");
    EXPECT_EQ(emptyArtist.getBio(), "");
}

TEST_F(ArtistTest, MinimalConstructor) {
    // Create a minimal artist
    database::Artist minimal {name};
    EXPECT_EQ(minimal.getId(), 0);
    EXPECT_EQ(minimal.getName(), name);
    EXPECT_EQ(minimal.getImgSource(), "");
    EXPECT_EQ(minimal.getBio(), "");
}


/**
 * Test setters
 */

TEST_F(ArtistTest, Setters) {
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

/**
 * Operators test
 */

TEST_F(ArtistTest, EqualOperatorTrue) {
    EXPECT_TRUE(artist == database::Artist(id, name, imgSource, bio));
}

TEST_F(ArtistTest, EqualOperatorFalse) {
    EXPECT_FALSE(artist == database::Artist(id, "Other name", imgSource, bio));
}



}  // namespace
