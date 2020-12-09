/**
 * LibraryMenuWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the LibraryMenuWidget class.
 *
 */

#include "LibraryMenuWidget.h"


namespace ui {


LibraryMenuWidget::LibraryMenuWidget()
    : Gtk::Box{Gtk::Orientation::ORIENTATION_VERTICAL},
      _libraryMenuTitle {"LIBRARY", Gtk::Align::ALIGN_START} 
{
    pack_start(_libraryMenuTitle, Gtk::PackOptions::PACK_SHRINK);
    pack_start(_savedSongsButton, Gtk::PackOptions::PACK_SHRINK);
    pack_start(_artistsButton,    Gtk::PackOptions::PACK_SHRINK);
    pack_start(_albumsButton,     Gtk::PackOptions::PACK_SHRINK);

    // Show widgets
    show_all_children();
}




LibraryMenuWidget::~LibraryMenuWidget()
{
}



}  // namespace ui 
