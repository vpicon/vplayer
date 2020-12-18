/** 
 * TrackTest.cpp
 *
 * Module: test/database
 *
 * Unit tests of the Track class.
 *
 */

#include "gtest/gtest.h"
#include "Track.h"
#include "Album.h"
#include "Artist.h"

#include <string>
#include <vector>


namespace {


// HELPER METHODS


// FIXTURE

class TrackTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    // Generate artists and albums for the 
    database::Artist artist1 {1, "Paul Desmond", "some_pic.png", ""};
    database::Artist artist2 {2, "Jim Hall", "jim_hall.png", "A nice guitarrist."};
    database::Album album {1, "The Best Of Paul Desmond", artist1, 1972, ""};
    std::string title {"Skylark"};
    std::string date {""};
    float duration {2.0};
    std::string source {"this.wav"};

    database::Track track {1, 
                           title, 
                           album, 
                           std::vector<database::Artist> {artist1}, 
                           date, 
                           duration, 
                           source};
};

// UNIT TESTS

/**
 * Test getters
 */

TEST_F(TrackTest, Getters) {
    EXPECT_EQ(track.getId(), 1);
    EXPECT_EQ(track.getTitle(), title);
    EXPECT_EQ(track.getAlbum(), album);
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {artist1});
    EXPECT_EQ(track.getDate(), date);
    EXPECT_EQ(track.getDuration(), duration);
    EXPECT_EQ(track.getSource(), source);
}



/**
 * hasAlbum() test:
 *      return: true, false, false then true
 */

TEST_F(TrackTest, HasAlbumTrue) {
    EXPECT_TRUE(track.hasAlbum());
}

TEST_F(TrackTest, HasAlbumFalse) {
    database::Track minimalTrack {"Minimal"};
    EXPECT_FALSE(minimalTrack.hasAlbum());
}

TEST_F(TrackTest, HasAlbumFalseThenTrue) {
    database::Track minimalTrack {"Minimal"};
    EXPECT_FALSE(minimalTrack.hasAlbum());

    // Add artist and album to the track
    minimalTrack.setArtists({artist1});
    minimalTrack.setAlbum(album);

    // Check if has album now
    EXPECT_TRUE(minimalTrack.hasAlbum());
}



/**
 * Test setters
 */

TEST_F(TrackTest, Setters) {
    // Define new values
    std::string newTitle {"OtherTrack"};
    database::Album newAlbum {2, "Bossa Antigua", artist1, 1970, ""};
    std::vector<database::Artist> newArtists {artist1, artist2};
    std::string newDate {"Other date"};
    float newDuration {1};
    std::string newSource {"other.mp3"};

    // Set new values
    track.setTitle(newTitle);
    track.setAlbum(newAlbum);
    track.setArtists(newArtists);
    track.setDate(newDate);
    track.setDuration(newDuration);
    track.setSource(newSource);

    // Test new values
    EXPECT_EQ(track.getId(), 1);
    EXPECT_EQ(track.getTitle(), newTitle);
    EXPECT_EQ(track.getAlbum(), newAlbum);
    EXPECT_EQ(track.getArtists(), newArtists);
    EXPECT_EQ(track.getDate(), newDate); 
    EXPECT_EQ(track.getDuration(), newDuration);
    EXPECT_EQ(track.getSource(), newSource);
}



/**
 * Test modifyers
 */

TEST_F(TrackTest, AddArtist) {
    // Check we cannot add the same artist to the track
    EXPECT_FALSE(track.addArtist(artist1));
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {artist1});

    // Check we can add a different artist to track
    EXPECT_TRUE(track.addArtist(artist2));

    // Check artist added to track
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist>({artist1, artist2}));
}

TEST_F(TrackTest, RemoveArtist) {
    // Check we cannot remove a missing artist from the track
    EXPECT_FALSE(track.removeArtist(artist2));
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {artist1});

    // Check we remove an artist from track
    EXPECT_TRUE(track.removeArtist(artist1));

    // Check artist added to track
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {});
}

TEST_F(TrackTest, UpdateArtist) {
    // Check we cannot update a missing artist from the track
    EXPECT_FALSE(track.updateArtist(artist2));
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {artist1});

    // Update same artist values
    artist1.setName("Other Name");

    // Check we remove an artist from track
    EXPECT_TRUE(track.updateArtist(artist1));

    // Check artist added to track
    EXPECT_EQ(track.getArtists(), std::vector<database::Artist> {artist1});
}


/**
 * Operators test.
 */

TEST_F(TrackTest, EqualOperatorTrue) {
    // Test with itself
    EXPECT_TRUE(track == track);

    // Test with album with same attributes
    EXPECT_TRUE(track == database::Track (1, title, album, 
                std::vector<database::Artist> {artist1}, date, duration, source));
}

TEST_F(TrackTest, EqualOperatorFalse) {
    // Test with empty album
    EXPECT_FALSE(track == database::Track{});

    // Test with album with other attributes
    EXPECT_FALSE(track == database::Track("Title"));
}



}  // namespace
