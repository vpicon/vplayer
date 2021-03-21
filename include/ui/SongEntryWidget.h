/**
 * SongEntryWidget.h
 *
 * Module: ui
 *
 * Defines SongEntryWidget class interface.
 *
 */

#ifndef _VPLAYER_SONG_ENTRY_WIDGET_H
#define _VPLAYER_SONG_ENTRY_WIDGET_H


#include "../database/Track.h"

#include <gtkmm/box.h>
#include <gtkmm/label.h>


namespace ui {


/**
 * Widget representing a single entry of a song into a list of 
 * songs widget. 
 */
class SongEntryWidget : public Gtk::Box {
public:
    SongEntryWidget(database::Track &tr);
    ~SongEntryWidget();
private:
    database::Track _track;
    Gtk::Label _titleLabel;  // temporal

    // TODO: Add labels and buttons for each field
};



}  // namespace ui 


#endif  // _VPLAYER_SONG_ENTRY_WIDGET_H
