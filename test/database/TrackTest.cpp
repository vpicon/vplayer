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


// FIXTURE

class TrackTest : public testing::Test {
protected:
    // No SetUp() needed
    // No TearDown() needed

    // Generate artists and albums for the 
    database::Artist artist1 {1, "Paul Desmond", "some_pic.png", ""};
    database::Artist artist2 {2, "Jim Hall", "jim_hall.png", "A nice guitarrist."};
    database::Album album {1, "The Best Of Paul Desmond", 1972, ""};
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

TEST_F(TrackTest, getters) {
    EXPECT_EQ(track.getId(), 1);
    EXPECT_EQ(track.getTitle(), title);
    albumsEqual(track.getAlbum(), album);
    listArtistsEqual(track.getArtists(), std::vector<database::Artist> {artist1});
    EXPECT_EQ(track.getDate(), date);
    EXPECT_EQ(track.getDuration(), duration);
    EXPECT_EQ(track.getSource(), source);
}



/**
 * Test setters
 */

TEST_F(TrackTest, setters) {
    // Define new values
    std::string newTitle {"OtherTrack"};
    database::Album newAlbum {2, "Bossa Antigua", 1970, ""};
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
    albumsEqual(track.getAlbum(), newAlbum);
    listArtistsEqual(track.getArtists(), newArtists);
    EXPECT_EQ(track.getDate(), newDate); 
    EXPECT_EQ(track.getDuration(), newDuration);
    EXPECT_EQ(track.getSource(), newSource);
}



/**
 * Test modifyers
 */

TEST_F(TrackTest, addArtistTest) {
    // Check we cannot add the same artist to the track
    EXPECT_FALSE(track.addArtist(artist1));
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {artist1});

    // Check we can add a different artist to track
    EXPECT_TRUE(track.addArtist(artist2));

    // Check artist added to track
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {artist1, artist2});
}

TEST_F(TrackTest, removeArtistTest) {
    // Check we cannot remove a missing artist from the track
    EXPECT_FALSE(track.removeArtist(artist2));
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {artist1});

    // Check we remove an artist from track
    EXPECT_TRUE(track.removeArtist(artist1));

    // Check artist added to track
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {});
}

TEST_F(TrackTest, updateArtistTest) {
    // Check we cannot update a missing artist from the track
    EXPECT_FALSE(track.updateArtist(artist2));
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {artist1});

    // Update same artist values
    artist1.setName("Other Name");

    // Check we remove an artist from track
    EXPECT_TRUE(track.updateArtist(artist1));

    // Check artist added to track
    listArtistsEqual(track.getArtists(), 
                     std::vector<database::Artist> {artist1});
}



}  // namespace
