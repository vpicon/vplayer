/**
 * LibraryPlaylistsMenuWidget.h
 *
 * Module: ui
 *
 * Defines LibraryPlaylistsMenuWidget class interface.
 *
 */

#ifndef _VPLAYER_LIBRARY_PLAYLISTS_MENU_WIDGET_H
#define _VPLAYER_LIBRARY_PLAYLISTS_MENU_WIDGET_H


#include "LibraryMenuWidget.h"

#include <gtkmm/box.h>
#include <gtkmm/button.h>


namespace ui {


/**
 * Menu on the left pannel of the application containing the library
 * menu and playlists menu.
 */
class LibraryPlaylistsMenuWidget : public Gtk::Box {
public:
    LibraryPlaylistsMenuWidget();
    ~LibraryPlaylistsMenuWidget();
private:
    LibraryMenuWidget _libraryMenu;
    Gtk::Button _playlistsMenu{"Playists Menu"};
};



}  // namespace ui 


#endif  // _VPLAYER_LIBRARY_PLAYLISTS_MENU_WIDGET_H
