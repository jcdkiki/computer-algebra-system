#include "window.hpp"

int main(int argc, char* argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.cas");
    CasWindow window;
    return app->run(window);
}
