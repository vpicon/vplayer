/** 
 * LibrarySQLiteDBTest_getters.cpp
 *
 * Module: test/database
 *
 * Unit tests of the LibrarySQLiteDBTest class getter methods.
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

class LibrarySQLiteDBGettersTest : public testing::Test {
protected:
    void TearDown() override {
        // Delete all tracks stored in the database
        for (database::Track &track : db.getAllTracks())
            ASSERT_TRUE(db.deleteTrack(track));
    }
    
    // Create database object
    database::LibrarySQLiteDB db {"test/.librarySqliteDB_getters.db"};

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
 * getAllTracks Tests: 
 *   vector size: 0, 1, >1
 */

// getAllTracks test with empty database
TEST_F(LibrarySQLiteDBGettersTest, GetAllTracksEmptyDatabase) {
    // Check empty vector from all tracks
    EXPECT_TRUE(db.getAllTracks().empty());
}



}  // namespace 
