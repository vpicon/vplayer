/**
 * MainWindow.h
 *
 * Module: ui
 *
 * Defines MainWindow class interface.
 *
 */

#ifndef _VPLAYER_MAIN_WINDOW_H
#define _VPLAYER_MAIN_WINDOW_H

#include <gtkmm/window.h>


namespace ui {


/**
 * Main window widget of the application. 
 */
class MainWindow : public Gtk::Window {
public:
    MainWindow();
    ~MainWindow();
};



}  // namespace ui 


#endif  // _VPLAYER_MAIN_WINDOW_H
