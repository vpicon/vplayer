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

#include <string>


namespace {


// HELPER METHODS


// FIXTURE

class AlbumTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    // Generate a new artist
    int id {10};
    std::string title {"MiniAlbum"};
    int year {1970};
    std::string imgSource {"/home/usr/some_image.jpg"};

    database::Album album {id, title, year, imgSource};

    // Generate a default constructor empty artist
    database::Album emptyAlbum {};
};

// UNIT TESTS

/**
 * Test getters
 */

TEST_F(AlbumTest, getters) {
    EXPECT_EQ(album.getId(), id);
    EXPECT_EQ(album.getTitle(), title);
    EXPECT_EQ(album.getYear(), year);
    EXPECT_EQ(album.getImgSource(), imgSource);
}


/**
 * Test default constructor
 */
TEST_F(AlbumTest, defaultConstructor) {
    EXPECT_EQ(emptyAlbum.getId(), 0);
    EXPECT_EQ(emptyAlbum.getTitle(), "");
    EXPECT_EQ(emptyAlbum.getYear(), 0);
    EXPECT_EQ(emptyAlbum.getImgSource(), "");
}


/**
 * Test setters
 */

TEST_F(AlbumTest, setters) {
    // Define new values
    std::string newTitle {"OtherAlbum"};
    int newYear {2000};
    std::string newImgSource {"/home/usr/x.jpg"};

    // Set new values
    album.setTitle(newTitle);
    album.setYear(newYear);
    album.setImgSource(newImgSource);

    // Test new values
    EXPECT_EQ(album.getId(), id);
    EXPECT_EQ(album.getTitle(), newTitle);
    EXPECT_EQ(album.getYear(), newYear);
    EXPECT_EQ(album.getImgSource(), newImgSource);
}



}  // namespace
