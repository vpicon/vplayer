/** 
 * LibrarySQLiteDBTest_inserters.cpp
 *
 * Module: test/database
 *
 * Unit tests of the LibrarySQLiteDBTest class inserter methods.
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

class LibrarySQLiteDBInsertersTest : public testing::Test {
protected:
    void SetUp() override {
        // Add track1 to the database
        ASSERT_TRUE(db.insertNewTrack(track1));
    }

    void TearDown() override {
        // Delete all tracks stored in the database
        for (database::Track &track : db.getAllTracks())
            ASSERT_TRUE(db.deleteTrack(track));
    }
    
    // Create database object
    database::LibrarySQLiteDB db {"test/.librarySqliteDB_inserters.db"};

    // Create track objects
    database::Artist artist1 {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Artist artist2 {"Jim Hall", "~/Pictures/jim_hall.jpg", "A guitar."};
    database::Artist minimalArtist {"Minimal Guy"};

    database::Album album {"Bossa Antigua", artist1, 1997, "~/Pictures/bossa_antigua.jpg"};
    database::Album minimalAlbum {"Minimal Collection", minimalArtist};

    database::Track track1 {"Bossa Antigua", album, {artist1, artist2}, "today", 432, "~/Music/bossa.mp3"};
    database::Track track2 {"O Gato", album, {artist1, artist2}, "yesterday", 11, "gatito.wav"};
    database::Track minimalTrack {"Minimalist"};
};

// UNIT TESTS

/**
 * insertNewTrack Tests: 
 *   track: new, already stored in the db
 *       title: always nonempty
 *       additionDate: always nonempty
 *       source: always nonempty
 *
 *   artists: empty, 1 artist, > 1 artist 
 *            new, already in db
 *       name: always nonempty
 *       imageSource: empty, nonempty
 *       bio: empty, nonempty
 *        
 *   album: empty, non empty
 *          new, already in db
 *       title: always nonempty
 *       Artist: valid
 *       year: any
 *       imageSource: empty, nonempty
 */

TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackMinimalTrack) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(minimalTrack));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(minimalTrack.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, minimalTrack);
}


TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackMinimalTrack) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(minimalTrack));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(minimalTrack.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, minimalTrack);
}



}  // namespace 
