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
    
    // Create track to add
    database::Artist paulDesmond {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Artist jimHall {"Jim Hall", "~/Pictures/jim_hall.jpg", "A guitar."};

    database::Album bossaAntiguaAlbum {"Bossa Antigua", paulDesmond, 1997, "~/Pictures/bossa_antigua.jpg"};

    database::Track bossaAntigua {"Bossa Antigua", bossaAntiguaAlbum, {paulDesmond, jimHall}, "today", 432, "~/Music/bossa.mp3"};
    database::Track oGato {"O Gato", bossaAntiguaAlbum, {paulDesmond, jimHall}, "yesterday", 11, "gatito.wav"};

    databse::Playlist playlist {"Jazz", "jazzy.jpeg", {bossaAntigua, oGato}};
    
    // Add track to database
    db.insertNewTrack(bossaAntigua);
    
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
