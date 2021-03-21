/**
 * ViewWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the ViewWidget class.
 *
 */

#include "ViewWidget.h"


namespace ui {


ViewWidget::ViewWidget()
    : Gtk::Box{Gtk::Orientation::ORIENTATION_VERTICAL},
      _topBar{"TOP BAR", Gtk::Align::ALIGN_START}
{
    // Add widgets to the box
    pack_start(_topBar, Gtk::PackOptions::PACK_SHRINK);
    pack_end(_songsView, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    // Add box of playlists to the scrolled window 
    // _scrollWin.add(_viewport);
    // _viewport.add(_playlistsBox);  
    // _playlistsBox.pack_start(_tmpPlaylist, Gtk::PackOptions::PACK_SHRINK);

    // Show widgets
    show_all_children();
}




ViewWidget::~ViewWidget()
{
}



}  // namespace ui 
