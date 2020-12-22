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

#include <algorithm>
#include <vector>


namespace {


// HELPER METHODS

template <class T>
bool vectorContains(const std::vector<T> &v, const T &x) {
    return std::find(v.begin(), v.end(), x) != v.end();
}


// FIXTURE

class LibrarySQLiteDBGettersTest : public testing::Test {
protected:
    void TearDown() override {
        // Delete all tracks stored in the database
        for (database::Track &track : db.getAllTracks())
            ASSERT_TRUE(db.deleteTrack(track));

        // Delete all playlists stored in database
        for (database::Playlist &playlist : db.getAllPlaylists())
            ASSERT_TRUE(db.deletePlaylist(playlist));
    }
    
    // Create database object
    database::LibrarySQLiteDB db {"test/.librarySqliteDB_getters.db"};

    // Create entity objects
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
    database::Album album4 {"Syncopated Soul", artist3, 2020, "~/Pictures/soul.jpg"};
    database::Track track3 {"Golden", album3, {artist3}, "now", 332, "Cory_Wong-Golden.wav"};
    database::Track track4 {"Restoration", album3, {artist3}, "now", 332, "Cory_Wong-Restoration.wav"};
    database::Track track5 {"Cosmic Sans", album4, {artist3}, "now", 332, "Cory_Wong-Sans.wav"};

    database::Playlist playlist1 {"Some Jazz", "jazz.jpg"};
    database::Playlist playlist2 {"Funky Duck", "funky.jpg"};
};

// UNIT TESTS

/**
 * getAllTracks Tests: 
 *   vector size: 0, 1, >1
 */

TEST_F(LibrarySQLiteDBGettersTest, GetAllTracksEmptyDatabase) {
    // Check empty vector from all tracks
    EXPECT_TRUE(db.getAllTracks().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllTracksOneTrack) {
    // Add one track to database
    db.insertNewTrack(track1);

    // Check vector contains only track 1
    ASSERT_EQ(db.getAllTracks().size(), 1u);
    EXPECT_EQ(db.getAllTracks()[0], track1);
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllTracksMultipleTracks) {
    // Add one track to database
    db.insertNewTrack(track1);
    db.insertNewTrack(track3);

    // Check vector contains both tracks
    ASSERT_EQ(db.getAllTracks().size(), 2u);

    EXPECT_TRUE(vectorContains<database::Track>(db.getAllTracks(), track1));
    EXPECT_TRUE(vectorContains<database::Track>(db.getAllTracks(), track3));
}



/**
 * getTrack Tests: 
 *   database tracks: 1, > 1
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

TEST_F(LibrarySQLiteDBGettersTest, GetTrackFullTrack) {
    // Add track to database
    db.insertNewTrack(track1);

    // Retrieve track from database with id gotten
    database::Track retrievedTrack {db.getTrack(track1.getId())};

    // Compare two tracks are equal
    EXPECT_EQ(retrievedTrack, track1);
}

TEST_F(LibrarySQLiteDBGettersTest, GetTrackMinimalTrack) {
    // Add track to database
    db.insertNewTrack(minimalTrack);

    // Retrieve track from database with id gotten
    database::Track retrievedTrack {db.getTrack(minimalTrack.getId())};

    // Compare two tracks are equal
    EXPECT_EQ(retrievedTrack, minimalTrack);
}

TEST_F(LibrarySQLiteDBGettersTest, GetTrackMinimalArtist) {
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
    // Add track to database
    db.insertNewTrack(theTrack);

    // Retrieve track from database with id gotten
    database::Track retrievedTrack {db.getTrack(theTrack.getId())};

    // Compare two tracks are equal
    EXPECT_EQ(retrievedTrack, theTrack);
}

TEST_F(LibrarySQLiteDBGettersTest, GetTrackMinimalAlbum) {
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

TEST_F(LibrarySQLiteDBGettersTest, GetTrackNonEmptyDatabase) {
    // Add track to database
    db.insertNewTrack(track3);
    db.insertNewTrack(track1);

    // Retrieve track from database with id gotten
    database::Track retrievedTrack {db.getTrack(track1.getId())};

    // Compare two tracks are equal
    EXPECT_EQ(retrievedTrack, track1);
}

/**
 * getAllPlaylists Tests: 
 *   vector size: 0, 1, >1
 *   TODO: tracks on playlists
 */

TEST_F(LibrarySQLiteDBGettersTest, GetAllPlaylistsNoPlaylists) {
    // Check empty vector from all Playlists
    EXPECT_TRUE(db.getAllPlaylists().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllPlaylistsOnePlaylist) {
    // Add one playlist to database
    db.insertNewPlaylist(playlist1);

    // Check vector contains only track 1
    ASSERT_EQ(db.getAllPlaylists().size(), 1u);
    // EXPECT_EQ(db.getAllPlaylists()[0], playlist1);
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllPlaylistsMultiplePlaylists) {
    // Add one playlist to database
    db.insertNewPlaylist(playlist1);
    db.insertNewPlaylist(playlist2);

    // Check vector contains both Playlists
    ASSERT_EQ(db.getAllPlaylists().size(), 2u);

    // EXPECT_TRUE(vectorContains<database::Playlist>(db.getAllPlaylists(), playlist1));
    // EXPECT_TRUE(vectorContains<database::Playlist>(db.getAllPlaylists(), playlist2));
}



/**
 * getAllAlbums Tests: 
 *   vector size: 0, 1, >1
 */

TEST_F(LibrarySQLiteDBGettersTest, GetAllAlbumsEmptyDatabase) {
    // Check empty vector from all Albums
    EXPECT_TRUE(db.getAllAlbums().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllAlbumsNonEmptyDatabaseNoAlbums) {
    // Add one track to database with no albums
    db.insertNewTrack(minimalTrack);

    // Check vector contains no albums
    ASSERT_TRUE(db.getAllAlbums().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllAlbumsOneTrackOneAlbum) {
    // Add one track to database
    db.insertNewTrack(track1);

    // Check vector contains only track 1
    ASSERT_EQ(db.getAllAlbums().size(), 1u);
    EXPECT_EQ(db.getAllAlbums()[0], track1.getAlbum());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllAlbumsMultipleTracksOneAlbum) {
    // Add one track to database
    db.insertNewTrack(track1);
    db.insertNewTrack(track2);

    // Check vector contains only track 1
    ASSERT_EQ(db.getAllAlbums().size(), 1u);
    EXPECT_EQ(db.getAllAlbums()[0], track1.getAlbum());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllAlbumsMultipleAlbums) {
    // Add one track to database
    db.insertNewTrack(track1);
    db.insertNewTrack(track3);

    // Check vector contains both Albums
    ASSERT_EQ(db.getAllAlbums().size(), 2u);

    EXPECT_TRUE(vectorContains<database::Album>(db.getAllAlbums(), track1.getAlbum()));
    EXPECT_TRUE(vectorContains<database::Album>(db.getAllAlbums(), track3.getAlbum()));
}



/**
 * getAlbumTracks Tests: 
 *   vector size: 1, >1
 */

TEST_F(LibrarySQLiteDBGettersTest, GetAlbumTracksMultipleTracks) {
    // Add one track to database
    db.insertNewTrack(track1);
    db.insertNewTrack(track2);

    // Check vector contains both Albums
    ASSERT_EQ(db.getAlbumTracks(track1.getAlbum()).size(), 2u);

    EXPECT_TRUE(vectorContains<database::Track>(db.getAlbumTracks(track1.getAlbum()), track1));
    EXPECT_TRUE(vectorContains<database::Track>(db.getAlbumTracks(track2.getAlbum()), track2));
}



/**
 * getAllArtists Tests: 
 *   vector size: 0, 1, >1
 */

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsEmptyDatabase) {
    // Check empty vector from all Artists
    EXPECT_TRUE(db.getAllArtists().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsNonEmptyDatabaseNoArtists) {
    // Add one track to database with no Artists
    db.insertNewTrack(minimalTrack);

    // Check vector contains no Artists
    ASSERT_TRUE(db.getAllArtists().empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsOneTrackOneArtist) {
    // Add one track to database
    db.insertNewTrack(track3);

    // Check vector contains single artist from track1
    ASSERT_EQ(db.getAllArtists().size(), 1u);
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track3.getArtists()[0]));
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsOneTrackMultipleArtist) {
    // Add one track to database
    db.insertNewTrack(track1);

    // Check vector contains both artists from track1
    ASSERT_EQ(db.getAllArtists().size(), 2u);
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track1.getArtists()[0]));
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track1.getArtists()[1]));
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsMultipleTracksOneArtists) {
    // Add one track to database
    db.insertNewTrack(track3);
    db.insertNewTrack(track4);

    // Check vector contains single artist from tracks 3 and 4
    ASSERT_EQ(db.getAllArtists().size(), 1u);
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track3.getArtists()[0]));
}

TEST_F(LibrarySQLiteDBGettersTest, GetAllArtistsMultipleAlbums) {
    // Add one track to database
    db.insertNewTrack(track1);
    db.insertNewTrack(track3);

    // Check vector contains both Artists
    ASSERT_EQ(db.getAllArtists().size(), 3u);

    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track1.getArtists()[0]));
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track1.getArtists()[1]));
    EXPECT_TRUE(vectorContains<database::Artist>(db.getAllArtists(), track3.getArtists()[0]));
}



/**
 * getArtistAlbums Tests: 
 *   vector size: 0, 1, >1
 */

TEST_F(LibrarySQLiteDBGettersTest, GetArtistAlbumsNoAlbums) {
    // Add artist to minimal track
    minimalTrack.addArtist(minimalArtist);
    
    // Add track with artist and no albums
    db.insertNewTrack(minimalTrack);

    // Check empty vector from all Artists
    EXPECT_TRUE(db.getArtistAlbums(minimalTrack.getArtists()[0]).empty());
}

TEST_F(LibrarySQLiteDBGettersTest, GetArtistAlbumsSingleAlbum) {
    // Add track with artist and no albums
    db.insertNewTrack(track3);

    // Check empty vector from all Artists
    EXPECT_TRUE(vectorContains<database::Album>(db.getArtistAlbums(track3.getArtists()[0]), 
                                                track3.getAlbum()));
}

TEST_F(LibrarySQLiteDBGettersTest, GetArtistAlbumsMultipleAlbums) {
    // Add track with artist and no albums
    db.insertNewTrack(track3);
    db.insertNewTrack(track5);

    // Check empty vector from all Artists
    EXPECT_TRUE(vectorContains<database::Album>(db.getArtistAlbums(track3.getArtists()[0]), 
                                                track3.getAlbum()));
    EXPECT_TRUE(vectorContains<database::Album>(db.getArtistAlbums(track5.getArtists()[0]), 
                                                track5.getAlbum()));
}



/**
 * existsTrack Tests: 
 *      result: true, false
 */

TEST_F(LibrarySQLiteDBGettersTest, ExistsTrackTrue) {
    // Add track to database
    db.insertNewTrack(track1);

    // Check there is track with source of track1
    EXPECT_TRUE(db.existsTrack(track1.getSource()));
}

TEST_F(LibrarySQLiteDBGettersTest, ExistsTrackFalseEmptyDatabase) {
    // Check there is track with source of track1
    EXPECT_FALSE(db.existsTrack(track1.getSource()));
}

TEST_F(LibrarySQLiteDBGettersTest, ExistsTrackFalseNonEmptyDatabase) {
    // Add track to database
    db.insertNewTrack(track4);

    // Check there is track with source of track1
    EXPECT_FALSE(db.existsTrack(track1.getSource()));
}


}  // namespace 
