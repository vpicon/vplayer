/**
 * ViewWidget.h
 *
 * Module: ui
 *
 * Defines ViewWidget class interface.
 *
 */

#ifndef _VPLAYER_VIEW_WIDGET_H
#define _VPLAYER_VIEW_WIDGET_H

#include "SongsViewWidget.h"

#include <gtkmm/box.h>
#include <gtkmm/label.h>


namespace ui {


/**
 * Widget placed in the right pane, holds the window view of the 
 * the music player, contains one kind of view at a time, depending
 * on what the user wants to see.
 */
class ViewWidget : public Gtk::Box {
public:
    ViewWidget();
    ~ViewWidget();
private:
    Gtk::Label _topBar;
    SongsViewWidget _songsView;

    // TODO:
    // Add a top bar (transparent and minimal) with and a stack controller
    // (previous and next window in stack), and a search bar.
    //
    // And a main stack widget. This will contain each of the views (or pages)
    // AlbumView, PlaylistView ...
};



}  // namespace ui 


#endif  // _VPLAYER_VIEW_WIDGET_H
