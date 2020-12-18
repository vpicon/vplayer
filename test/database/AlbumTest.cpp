/** 
 * AlbumTest.cpp
 *
 * Module: test/database
 *
 * Unit tests of the Album class.
 *
 */

#include "gtest/gtest.h"
#include "Album.h"
#include "Artist.h"

#include <string>


namespace {


// HELPER METHODS

void artistsEqual(const database::Artist &artist1, const database::Artist &artist2) {
    EXPECT_EQ(artist1.getId(), artist2.getId());
    EXPECT_EQ(artist1.getName(), artist2.getName());
    EXPECT_EQ(artist1.getImgSource(), artist2.getImgSource());
    EXPECT_EQ(artist1.getBio(), artist2.getBio());
}


// FIXTURE

class AlbumTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    // Generate a new artist
    int id {10};
    std::string title {"MiniAlbum"};
    database::Artist artist {"John Butler", "johnny.jpeg", "A nice guitar player."};
    int year {1970};
    std::string imgSource {"/home/usr/some_image.jpg"};

    database::Album album {id, title, artist, year, imgSource};

    // Generate a default constructor empty artist
    database::Album emptyAlbum {};
};

// UNIT TESTS

/**
 * Test getters
 */

TEST_F(AlbumTest, Getters) {
    EXPECT_EQ(album.getId(), id);
    EXPECT_EQ(album.getTitle(), title);
    artistsEqual(album.getArtist(), artist);
    EXPECT_EQ(album.getYear(), year);
    EXPECT_EQ(album.getImgSource(), imgSource);
}


/**
 * Test default constructor
 */
TEST_F(AlbumTest, DefaultConstructor) {
    EXPECT_EQ(emptyAlbum.getId(), 0);
    EXPECT_EQ(emptyAlbum.getTitle(), "");
    artistsEqual(emptyAlbum.getArtist(), database::Artist{});
    EXPECT_EQ(emptyAlbum.getYear(), 0);
    EXPECT_EQ(emptyAlbum.getImgSource(), "");
}


/**
 * Test setters
 */

TEST_F(AlbumTest, Setters) {
    // Define new values
    int newId {81241};
    std::string newTitle {"OtherAlbum"};
    database::Artist newArtist {"Other name", "joeg", "Ar."};
    int newYear {2000};
    std::string newImgSource {"/home/usr/x.jpg"};

    // Set new values
    album.setId(newId);
    album.setTitle(newTitle);
    album.setArtist(newArtist);
    album.setYear(newYear);
    album.setImgSource(newImgSource);

    // Test new values
    EXPECT_EQ(album.getId(), newId);
    EXPECT_EQ(album.getTitle(), newTitle);
    artistsEqual(album.getArtist(), newArtist);
    EXPECT_EQ(album.getYear(), newYear);
    EXPECT_EQ(album.getImgSource(), newImgSource);
}



/**
 * Operators Test
 */

TEST_F(AlbumTest, EqualOperatorTrue) {
    // Test with itself
    EXPECT_TRUE(album == album);

    // Test with album with same attributes
    EXPECT_TRUE(album == database::Album(id, title, artist, year, imgSource));
}

TEST_F(AlbumTest, EqualOperatorFalse) {
    // Test with empty album
    EXPECT_FALSE(album == database::Album{});

    // Test with album with other attributes
    EXPECT_FALSE(album == database::Album(id, "Other things", database::Artist{}, year, imgSource));
}



}  // namespace
