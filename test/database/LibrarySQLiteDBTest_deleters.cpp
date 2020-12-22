/** 
 * LibrarySQLiteDBTest_deleters.cpp
 *
 * Module: test/database
 *
 * Unit tests of the LibrarySQLiteDBTest class deleter methods.
 *
 */

#include "gtest/gtest.h"
#include "LibrarySQLiteDB.h"
#include "Track.h"
#include "Artist.h"
#include "Album.h"


namespace {


// HELPER METHODS


// FIXTURE

class LibrarySQLiteDBDeletersTest : public testing::Test {
protected:
    void TearDown() override {
        // Delete all tracks stored in the database
        for (database::Track &track : db.getAllTracks())
            ASSERT_TRUE(db.deleteTrack(track));
    }
    
    // Create database object
    database::LibrarySQLiteDB db {"test/.librarySqliteDB_deleters.db"};

    // Create track objects
    database::Artist artist1 {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Artist artist2 {"Jim Hall", "~/Pictures/jim_hall.jpg", "A guitar."};
    database::Artist minimalArtist {"Minimal Guy"};

    database::Album album {"Bossa Antigua", artist1, 1997, "~/Pictures/bossa_antigua.jpg"};
    database::Album minimalAlbum {"Minimal Collection", minimalArtist};

    database::Track track1 {"Bossa Antigua", album, {artist1, artist2}, "today", 432, "~/Music/bossa.mp3"};
    database::Track track2 {"O Gato", album, {artist1, artist2}, "yesterday", 11, "gatito.wav"};
    database::Track minimalTrack {"Minimalist"};

    database::Artist artist3 {"Cory Wong", "~/Pictures/cory_wong.jpg", "A nice strummer."};
    database::Album album3 {"Elevator Music for an Elevated Mood", artist3, 2020, "~/Pictures/elevator.jpg"};
    database::Track track3 {"Golden", album3, {artist3}, "now", 332, "Cory_Wong-Golden.wav"};
    database::Track track4 {"Restoration", album3, {artist3}, "now", 332, "Cory_Wong-Restoration.wav"};
};

// UNIT TESTS

/**
 * deleteTrack Tests: 
 *     number of tracks in db: 1, >1
 *     track artists: none, 1 artist, > 1 artist 
 *                    yes/not shared by other tracks in db
 *     track album: none, yes
 *                  yes/not shared by other tracks in db
 */

// deleteTrack minimal track, to a database containing only such track.
TEST_F(LibrarySQLiteDBDeletersTest, DeleteMinimalTrack) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(minimalTrack));

    // Delete the track from database
    ASSERT_TRUE(db.deleteTrack(minimalTrack));

    // Check Database empty
    EXPECT_EQ(db.getAllTracks().size(), 0u);
    EXPECT_EQ(db.getAllArtists().size(), 0u);
    EXPECT_EQ(db.getAllAlbums().size(), 0u);
}

// deleteTrack from a database containing multiple tracks.
TEST_F(LibrarySQLiteDBDeletersTest, DeleteTrackFromMultipleTrackDatabase) {
    // Insert the new track, should return true on success 
    ASSERT_TRUE(db.insertNewTrack(track1));
    ASSERT_TRUE(db.insertNewTrack(track3));

    // Delete the track from database
    ASSERT_TRUE(db.deleteTrack(track1));

    // Check Database contains single track, album and artist
    EXPECT_EQ(db.getAllTracks().size(), 1u);
    EXPECT_EQ(db.getAllTracks()[0], track3);
    EXPECT_EQ(db.getAllArtists().size(), 1u);
    EXPECT_EQ(db.getAllArtists()[0], track3.getArtists()[0]);
    EXPECT_EQ(db.getAllAlbums().size(), 1u);
    EXPECT_EQ(db.getAllAlbums()[0], track3.getAlbum());
}


}  // namespace 
