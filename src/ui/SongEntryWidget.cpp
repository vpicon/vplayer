/**
 * SongEntryWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the SongEntryWidget class.
 *
 */

#include "SongEntryWidget.h"


namespace ui {


SongEntryWidget::SongEntryWidget(database::Track &tr)
    : Gtk::Box{Gtk::Orientation::ORIENTATION_HORIZONTAL},
      _track{tr},
      _titleLabel{tr.getTitle(), Gtk::Align::ALIGN_START} 
{
    // Add widgets to the box
    pack_start(_titleLabel, Gtk::PackOptions::PACK_SHRINK);
    // pack_end(_songsView, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    // Show widgets
    show_all_children();
}



}  // namespace ui 
