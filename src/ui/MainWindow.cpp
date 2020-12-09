/**
 * MainWindow.cpp
 *
 * Module: ui
 *
 * Implementation of the MainWindow class.
 *
 */

#include "MainWindow.h"


namespace ui {


MainWindow::MainWindow()
    : _playerLibraryBox {Gtk::Orientation::ORIENTATION_VERTICAL},
      _libraryViewPane  {Gtk::Orientation::ORIENTATION_HORIZONTAL},
      _player {"Player"}
{
    // Set window properties
    set_title("VPlayer Music");
    maximize();

    // Set the horizontal pane in the window
    add(_playerLibraryBox);

    // Add elements to the box and set spacing
    _playerLibraryBox.pack_start(_libraryViewPane, 
                                 Gtk::PackOptions::PACK_EXPAND_WIDGET);
    _playerLibraryBox.pack_end(_player, 
                               Gtk::PackOptions::PACK_SHRINK);

    int boxInnerSpacing = 1;
    _playerLibraryBox.set_spacing(boxInnerSpacing);

    // Add elements to the pane
    _libraryViewPane.add1(b1);
    _libraryViewPane.add2(b2);

    // Show widgets
    show_all_children();
}



MainWindow::~MainWindow()
{
}



}  // namespace ui 
