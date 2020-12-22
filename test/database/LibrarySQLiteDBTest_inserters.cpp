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
    /*
    void SetUp() override {
        // Add track1 to the database
        ASSERT_TRUE(db.insertNewTrack(track1));
    }
    */

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

    database::Artist artist3 {"Cory Wong", "~/Pictures/cory_wong.jpg", "A nice strummer."};
    database::Album album3 {"Elevator Music for an Elevated Mood", artist3, 2020, "~/Pictures/elevator.jpg"};
    database::Track track3 {"Golden", album3, {artist3}, "now", 332, "Cory_Wong-Golden.wav"};
    database::Track track4 {"Restoration", album3, {artist3}, "now", 332, "Cory_Wong-Restoration.wav"};
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

// insertNewTrack a fully featured track (no minimal track, nor minimal album,
// nor minimal artist), to an empty database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackFullAll) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(track3));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(track3.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, track3);
}

// insertNewTrack a minimal track, to an empty database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackMinimalTrack) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(minimalTrack));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(minimalTrack.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, minimalTrack);
}

// insertNewTrack a track with various artists
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackVariousArtists) {
    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(track1));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(track1.getId());

    // Check we did add both artists
    ASSERT_EQ(db.getAllArtists().size(), 2u);

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, track1);
}

// insertNewTrack a minimal track, to an empty database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackMinimalArtist) {
    // Create a new track with minimal artist only
    database::Album theAlbum {"Collection by Minimalists", 
                                minimalArtist, 
                                2000, 
                                "~/Pictures/collectionByMinimalists.jpg"};
    database::Track theTrack {"Some Track", 
                              theAlbum, 
                              {minimalArtist}, 
                              "today", 
                              432, 
                              "~/Music/bossa.mp3"};

    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(theTrack));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(theTrack.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, theTrack);
}

// insertNewTrack a minimal track, to empty database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackMinimalAlbum) {
    // Create a new track with minimal artist only
    database::Track theTrack {"Some Track", 
                              minimalAlbum, 
                              {minimalAlbum.getArtist()}, 
                              "this day", 
                              13, 
                              "~/Music/bossa.mp3"};

    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(theTrack));

    // Check if the track is stored in the database
    database::Track retrievedTrack = db.getTrack(theTrack.getId());

    // Compare two tracks
    EXPECT_EQ(retrievedTrack, theTrack);
}

// insertNewTrack a track with an artist already stored in database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackStoredArtist) {
    // Insert first a track
    ASSERT_TRUE(db.insertNewTrack(track3));

    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(track4));

    // Check if the track is stored in the database and compare them
    database::Track retrievedTrack = db.getTrack(track4.getId());
    EXPECT_EQ(retrievedTrack, track4);

    // Check we did not add the artist again
    ASSERT_EQ(db.getAllArtists().size(), 1u);

    // Check track3 and track4 have the same artists (id may be changed)
    EXPECT_EQ(track3.getArtists(), track4.getArtists());

}

// insertNewTrack a track with an album already stored in database.
TEST_F(LibrarySQLiteDBInsertersTest, InsertNewTrackStoredAlbum) {
    // Insert first a track
    ASSERT_TRUE(db.insertNewTrack(track1));

    // Insert the new track, should return true on success
    ASSERT_TRUE(db.insertNewTrack(track2));

    // Check if the track is stored in the database and compare them
    database::Track retrievedTrack = db.getTrack(track2.getId());
    EXPECT_EQ(retrievedTrack, track2);

    // Check we did not add the artist again
    ASSERT_EQ(db.getAllAlbums().size(), 1u);
}



}  // namespace 
