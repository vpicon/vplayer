/** 
 * PlaylistTest.cpp
 *
 * Module: test/database
 *
 * Unit tests of the Playlist class.
 *
 */

#include "gtest/gtest.h"
#include "Playlist.h"
#include "Track.h"
#include "Artist.h"
#include "Album.h"

#include <string>
#include <vector>


namespace {


// HELPER METHODS

// FIXTURE

class PlaylistTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    
    // Create some tracks to generate the playlists
    database::Artist artist {1, "Paul Desmond", "some_pic.png", ""};
    database::Album album {1, "The Best Of Paul Desmond", artist, 1972, ""};

    database::Track track1 {1, "Skylark", album, 
                            std::vector<database::Artist> {artist}, "", 0.0, ""};
    database::Track track2 {2, "Take Ten", album, 
                            std::vector<database::Artist> {artist}, "", 0.0, ""};
    database::Track track3 {3, "Take Twelve", album, 
                            std::vector<database::Artist> {artist}, "", 0.0, ""};

    // Generate a new Playlist
    int id {10};
    std::string name {"Simple Playlist"};
    std::string imgSource {"/home/usr/some_image.jpg"};
    std::vector<database::Track> tracks {track1};

    database::Playlist playlist {id, name, imgSource, tracks};
};

// UNIT TESTS

/**
 * Test getters
 */

TEST_F(PlaylistTest, gettersTest) {
    EXPECT_EQ(playlist.getId(), id);
    EXPECT_EQ(playlist.getName(), name);
    EXPECT_EQ(playlist.getImgSource(), imgSource);
    EXPECT_EQ(playlist.getTracks(), tracks);
}

TEST_F(PlaylistTest, numTracksTest) {
    EXPECT_EQ(playlist.numTracks(), static_cast<int>(tracks.size()));
}



/**
 * Test setters
 */

TEST_F(PlaylistTest, settersTest) {
    // Define new values
    std::string newName {"Less Simple Playlist"};
    std::string newImgSource {"other_source.png"};
    std::vector<database::Track> newTracks {track1, track2};

    // Set new values
    playlist.setName(newName);
    playlist.setImgSource(newImgSource);
    playlist.setTracks(newTracks);

    // Test new values
    EXPECT_EQ(playlist.getId(), id);
    EXPECT_EQ(playlist.getName(), newName);
    EXPECT_EQ(playlist.getImgSource(), newImgSource);
    EXPECT_EQ(playlist.getTracks(), newTracks);
}



/**
 * addTrack() Test 
 */

TEST_F(PlaylistTest, addTrackAtBeginningTest) {
    // Add one track to the beginning of the playlist
    playlist.addTrack(track2, 0);

    // Check tracks 
    EXPECT_EQ(playlist.numTracks(), 2);
    EXPECT_EQ(playlist.getTracks()[0], track2);
}

TEST_F(PlaylistTest, addTrackAtEndTest) {
    // Add one track to the beginning of the playlist
    playlist.addTrack(track2, playlist.numTracks());

    // Check tracks 
    EXPECT_EQ(playlist.numTracks(), 2);
    EXPECT_EQ(playlist.getTracks()[1], track2);
}

TEST_F(PlaylistTest, addTrackAtMiddleTest) {
    // Add one track to the beginning of the playlist
    playlist.addTrack(track2, playlist.numTracks());
    playlist.addTrack(track3, playlist.numTracks() - 1);

    // Check tracks 
    EXPECT_EQ(playlist.numTracks(), 3);
    EXPECT_EQ(playlist.getTracks()[1], track3);
}



}  // namespace
