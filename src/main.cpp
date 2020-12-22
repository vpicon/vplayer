#define DEBUG 1
#if DEBUG


#include "database/LibrarySQLiteDB.h"
#include "database/Track.h"
#include "database/Album.h"
#include "database/Artist.h"
#include "database/Playlist.h"

#include <iostream>
#include <string>


int main() {
    // Create database
    database::LibrarySQLiteDB db {"hola.db"};
    
    // Create artist and albums
    database::Artist paulDesmond {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Artist jimHall {"Jim Hall", "~/Pictures/jim_hall.jpg", "A guitar."};

    database::Album bossaAntiguaAlbum {"Bossa Antigua", paulDesmond, 1997, "~/Pictures/bossa_antigua.jpg"};

    // Create traks and add them to database
    database::Track bossaAntigua {"Bossa Antigua", bossaAntiguaAlbum, {paulDesmond, jimHall}, "today", 432, "~/Music/bossa.mp3"};
    db.insertNewTrack(bossaAntigua);
    database::Track oGato {"O Gato", bossaAntiguaAlbum, {paulDesmond}, "yesterday", 11, "gatito.wav"};
    db.insertNewTrack(oGato);

    // Create new playlist
    // database::Playlist playlist {"Jazz", "jazzy.jpeg"};
    // db.insertNewPlaylist(playlist);
    
    // Add track to database
    // db.addTrackToPlaylist(bossaAntigua, playlist, playlist.numTracks());
    // db.addTrackToPlaylist(oGato, playlist, 0);
    
    db.deleteTrack(bossaAntigua);

    int count = 1;
    for (auto &artist : db.getAllArtists())
        std::cout << "Artist " << count++ << ": " << artist << std::endl;

    return 0;
}


#else  // NOT DEBUG


#include "ui/MainWindow.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv);
    ui::MainWindow mainWindow {};

    return app->run(mainWindow);
}


#endif // DEBUG
