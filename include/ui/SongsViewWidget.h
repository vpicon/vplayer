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

#include <gtkmm/scrolledwindow.h>
#include <gtkmm/viewport.h>
#include <gtkmm/box.h>


namespace ui {


/**
 * Widget placed in the right pane, holds the window view of the 
 * the music player, contains one kind of view at a time, depending
 * on what the user wants to see.
 */
class SongsViewWidget : public Gtk::ScrolledWindow {
public:
    SongsViewWidget();
    ~SongsViewWidget();
private:
    Gtk::Viewport _viewport;     // Wrapper for box to make it scrollable
    Gtk::Box _songsViewBox;  // two subcontainers separating player from upview
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
