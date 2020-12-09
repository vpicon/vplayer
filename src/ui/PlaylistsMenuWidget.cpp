/**
 * PlaylistsMenuWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the PlaylistsMenuWidget class.
 *
 */

#include "PlaylistsMenuWidget.h"


namespace ui {


PlaylistsMenuWidget::PlaylistsMenuWidget()
    : Gtk::Box{Gtk::Orientation::ORIENTATION_VERTICAL},
      _playlistsMenuTitle {"PLAYLISTS", Gtk::Align::ALIGN_START},
      _viewport{_scrollWin.get_hadjustment(), _scrollWin.get_vadjustment()},
      _playlistsBox{Gtk::Orientation::ORIENTATION_VERTICAL}
{
    // Add widgets to the box
    pack_start(_playlistsMenuTitle, Gtk::PackOptions::PACK_SHRINK);
    pack_end(_scrollWin, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    // Add box of playlists to the scrolled window 
    _scrollWin.add(_viewport);
    _viewport.add(_playlistsBox);  
    _playlistsBox.pack_start(_tmpPlaylist, Gtk::PackOptions::PACK_SHRINK);

    // Show widgets
    show_all_children();
}




PlaylistsMenuWidget::~PlaylistsMenuWidget()
{
}



}  // namespace ui 
