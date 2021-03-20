
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

#include <gtkmm/button.h>


namespace ui {


/**
 * Widget placed in the right pane, holds the window view of the 
 * the music player, contains one kind of view at a time, depending
 * on what the user wants to see.
 */
class ViewWidget : public Gtk::Button {
public:
    ViewWidget();
    ~ViewWidget();
private:
    // TODO:
    // Add a top bar (transparent and minimal), with a stack controller
    // (previous and next window in stack), and a search bar.
    //
    // And a main stack widget. This will contain each of the views (or pages)
    // AlbumView, PlaylistView ...
};



}  // namespace ui 


#endif  // _VPLAYER_VIEW_WIDGET_H
