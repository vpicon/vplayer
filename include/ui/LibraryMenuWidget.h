/**
 * LibraryMenuWidget.h
 *
 * Module: ui
 *
 * Defines LibraryMenuWidget class interface.
 *
 */

#ifndef _VPLAYER_LIBRARY_MENU_WIDGET_H
#define _VPLAYER_LIBRARY_MENU_WIDGET_H

#include <gtkmm/box.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>


namespace ui {


/**
 * Menu on the left pannel of the application containing the library
 * menu.
 */
class LibraryMenuWidget : public Gtk::Box {
public:
    LibraryMenuWidget();
    ~LibraryMenuWidget();
private:
    Gtk::Label _libraryMenuTitle;
    Gtk::Button _savedSongsButton{"Saved Songs"};
    Gtk::Button _artistsButton{"Artists"};
    Gtk::Button _albumsButton{"Albums"};
};



}  // namespace ui 


#endif  // _VPLAYER_LIBRARY_MENU_WIDGET_H
