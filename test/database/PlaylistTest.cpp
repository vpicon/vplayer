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

void artistsEqual(const database::Artist &artist1, const database::Artist &artist2) {
    EXPECT_EQ(artist1.getId(),        artist2.getId());
    EXPECT_EQ(artist1.getName(),      artist2.getName());
    EXPECT_EQ(artist1.getImgSource(), artist2.getImgSource());
    EXPECT_EQ(artist1.getBio(),       artist2.getBio());
}

void albumsEqual(const database::Album &album1, const database::Album &album2) {
    EXPECT_EQ(album1.getId(),        album2.getId());
    EXPECT_EQ(album1.getTitle(),     album2.getTitle());
    EXPECT_EQ(album1.getYear(),      album2.getYear());
    EXPECT_EQ(album1.getImgSource(), album2.getImgSource());
}

void listArtistsEqual(const std::vector<database::Artist> &v1,
                      const std::vector<database::Artist> &v2) 
{
    ASSERT_EQ(v1.size(), v2.size());
    
    for (size_t i = 0; i < v1.size(); i++)
        artistsEqual(v1[i], v2[i]);
}

void tracksEqual(const database::Track &track1,
                 const database::Track &track2)
{
    EXPECT_EQ(track1.getId(), track2.getId());
    EXPECT_EQ(track1.getTitle(), track2.getTitle());
    albumsEqual(track1.getAlbum(), track2.getAlbum());
    listArtistsEqual(track1.getArtists(), track2.getArtists());
    EXPECT_EQ(track1.getDate(), track2.getDate());
    EXPECT_EQ(track1.getDuration(), track2.getDuration());
    EXPECT_EQ(track1.getSource(), track2.getSource());
}

void listTracksEqual(const std::vector<database::Track> &tracklist1,
                     const std::vector<database::Track> &tracklist2) 
{
    ASSERT_EQ(tracklist1.size(), tracklist2.size());
    
    for (size_t i = 0; i < tracklist1.size(); i++)
        tracksEqual(tracklist1[i], tracklist2[i]);
}



// FIXTURE

class PlaylistTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed
    
    // Create some tracks to generate the playlists
    database::Artist artist {1, "Paul Desmond", "some_pic.png", ""};
    database::Album album {1, "The Best Of Paul Desmond", 1972, ""};

    database::Track track1 {1, "Skylark", album, 
                            std::vector<database::Artist> {artist}, "", 0.0, ""};
    database::Track track2 {2, "Take Ten", album, 
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
    listTracksEqual(playlist.getTracks(), tracks);
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
    listTracksEqual(playlist.getTracks(), newTracks);
}



}  // namespace
