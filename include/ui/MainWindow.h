/**
 * MainWindow.h
 *
 * Module: ui
 *
 * Defines MainWindow class interface.
 *
 */

#ifndef _VPLAYER_MAIN_WINDOW_H
#define _VPLAYER_MAIN_WINDOW_H


#include "PlayerWidget.h"
#include "LibraryPlaylistsMenuWidget.h"
#include "ViewWidget.h"

#include <gtkmm/applicationwindow.h>
#include <gtkmm/box.h>
#include <gtkmm/paned.h>
#include <gtkmm/button.h>


namespace ui {


/**
 * Toplevel window widget of the application. 
 */
class MainWindow : public Gtk::ApplicationWindow {
public:
    MainWindow();
    ~MainWindow();

private:
    Gtk::Box _playerLibraryBox;  // two subcontainers separating player from upview
    Gtk::Paned _libraryViewPane; // Side by side panes of library and view widget

    // PlayerWidget _playerWidget;
    PlayerWidget _player;         // temporary button object to simulate the player widget
    LibraryPlaylistsMenuWidget _menu;
    ViewWidget _view;
};



}  // namespace ui 



#endif  // _VPLAYER_MAIN_WINDOW_H
