/**
 * LibraryPlaylistsMenuWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the LibraryPlaylistsMenuWidget class.
 *
 */

#include "LibraryPlaylistsMenuWidget.h"


namespace ui {


LibraryPlaylistsMenuWidget::LibraryPlaylistsMenuWidget() 
    : Gtk::Box {Gtk::Orientation::ORIENTATION_VERTICAL}
{
    // Add elements to the box and set spacing
    pack_start(_libraryMenu, Gtk::PackOptions::PACK_SHRINK);
    pack_end(_playlistsMenu, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    int boxInnerSpacing = 1;
    set_spacing(boxInnerSpacing);
}




LibraryPlaylistsMenuWidget::~LibraryPlaylistsMenuWidget()
{
}



}  // namespace ui 
