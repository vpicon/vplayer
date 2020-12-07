#include "ui/MainWindow.h"
#include <gtkmm/application.h>

int main(int argc, char *argv[]) {
    auto app = Gtk::Application::create(argc, argv);
    ui::MainWindow mainWindow {};

    return app->run(mainWindow);
}
