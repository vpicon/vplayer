/**
 * PlayerWidget.h
 *
 * Module: ui
 *
 * Defines PlayerWidget class interface.
 *
 */

#ifndef _VPLAYER_PLAYER_WIDGET_H
#define _VPLAYER_PLAYER_WIDGET_H

#include <gtkmm/button.h>


namespace ui {


/**
 * Widget placed down in the window, holds the graphical interface for
 * the music player. 
 */
class PlayerWidget : public Gtk::Button {
public:
    PlayerWidget();
    ~PlayerWidget();
private:
};



}  // namespace ui 


#endif  // _VPLAYER_PLAYER_WIDGET_H
