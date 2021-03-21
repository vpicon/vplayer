/**
 * SongsViewWidget.cpp
 *
 * Module: ui
 *
 * Implementation of the SongsViewWidget class.
 *
 */

#include "SongsViewWidget.h"


namespace ui {


SongsViewWidget::SongsViewWidget()
    : _viewport{Gtk::ScrolledWindow::get_hadjustment(), Gtk::ScrolledWindow::get_vadjustment()},
      _songsViewBox{Gtk::Orientation::ORIENTATION_VERTICAL},
      _l1{"Saved Songs", Gtk::Align::ALIGN_START},
      _l2{"Some Label", Gtk::Align::ALIGN_START}
{
    // Add widgets to the view
    Gtk::ScrolledWindow::add(_viewport);
    _viewport.add(_songsViewBox);

    // Add widgets to songsView box
    _songsViewBox.pack_start(_l1, Gtk::PackOptions::PACK_SHRINK);
    _songsViewBox.pack_end(_songList, Gtk::PackOptions::PACK_EXPAND_WIDGET);

    // Create list of songs
    _songList.append(_song);
    _songList.append(_l2);
    
    // Show widgets
    show_all_children();
}



SongsViewWidget::~SongsViewWidget()
{
}



}  // namespace ui 
