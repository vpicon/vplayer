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
    : _viewport{Gtk::ScrolledWindow::get_hadjustment(), Gtk::ScrolledWindow::get_vadjustment()}
{
    // Add widgets to the view
    Gtk::ScrolledWindow::add(_viewport);
    _viewport.add(_songsViewBox);
    
    // Show widgets
    show_all_children();
}



SongsViewWidget::~SongsViewWidget()
{
}



}  // namespace ui 
