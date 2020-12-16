#define DEBUG 1
#if DEBUG


#include "database/LibrarySQLiteDB.h"
#include "database/Track.h"
#include "database/Album.h"
#include "database/Artist.h"

#include <iostream>
#include <string>


int main() {
    // Create database object
    database::LibrarySQLiteDB db{"hola.db"};

    database::Artist paulDesmond {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Album bossaAntiguaAlbum {"Bossa Antigua", paulDesmond, 1997, "~/Pictures/bossa_antigua.jpg"};

    db.insertNewAlbum(bossaAntiguaAlbum);

    std::cout << db.getAlbumByTitleAndArtist("Bossa Antigua", 1) 
              << std::endl;

    return 0;
    /*
    // Create track to add
    database::Artist paulDesmond {"Paul Desmond", "~/Pictures/paul_demond.jpg", "A nice saxo."};
    database::Artist jimHall {"Jim Hall", "~/Pictures/jim_hall.jpg", "A guitar."};

    database::Album bossaAntiguaAlbum {"Bossa Antigua", paulDesmond, 1997, "~/Pictures/bossa_antigua.jpg"};

    database::Track bossaAntigua {"Bossa Antigua", bossaAntiguaAlbum, {paulDesmond, jimHall}, "today", 432, "~/Music/bossa.mp3"};
    
    // Add track to database
    db.insertNewTrack(bossaAntigua);
    
    */
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
