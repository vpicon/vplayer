/**
 * PlaylistsMenuWidget.h
 *
 * Module: ui
 *
 * Defines PlaylistsMenuWidget class interface.
 *
 */

#ifndef _VPLAYER_PLAYLISTS_MENU_WIDGET_H
#define _VPLAYER_PLAYLISTS_MENU_WIDGET_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>


namespace ui {


/**
 * Menu on the left pannel of the application containing the playlists
 * menu.
 */
class PlaylistsMenuWidget : public Gtk::Box {
public:
    PlaylistsMenuWidget();
    ~PlaylistsMenuWidget();
private:
    Gtk::Label _playlistsMenuTitle;
    Gtk::ScrolledWindow _scrollWin;

    Gtk::Viewport _viewport;
    Gtk::Box _playlistsBox;

    Gtk::Label _tmpPlaylist{"Jazz"};
};



}  // namespace ui 


#endif  // _VPLAYER_PLAYLISTS_MENU_WIDGET_H
