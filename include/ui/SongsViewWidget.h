/**
 * SongsViewWidget.h
 *
 * Module: ui
 *
 * Defines SongsViewWidget class interface.
 *
 */

#ifndef _VPLAYER_SONGS_VIEW_WIDGET_H
#define _VPLAYER_SONGS_VIEW_WIDGET_H

#include "database/Track.h"
#include "SongEntryWidget.h"

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include <gtkmm/box.h>
#include <gtkmm/listbox.h>

#include <gtkmm/label.h>  // temporal


namespace ui {


/**
 * TODO:
 */
class SongsViewWidget : public Gtk::ScrolledWindow {
public:
    SongsViewWidget();
    ~SongsViewWidget();
private:
    Gtk::Viewport _viewport;  // Wrapper for box to make it scrollable
    Gtk::Box _songsViewBox;   // two subcontainers separating player from upview
    Gtk::ListBox _songList;   // list of songs 

    // temporal
    Gtk::Label _l1; 
    database::Track _track{"Test Track"};
    SongEntryWidget _song{_track};
    Gtk::Label _l2; 

    // TODO:
    // Add a two element horizontal box. 
    //
    // Top element for the title and some other information 
    // (i.e. play button, filter...).
    //
    // The other element is the GtkListBox
};



}  // namespace ui 


#endif  // _VPLAYER_SONGS_VIEW_WIDGET_H
