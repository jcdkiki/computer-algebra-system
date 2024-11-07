#include "window.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create("org.gtkmm.cas");
    return app->make_window_and_run<CasWindow>(argc, argv);
}
