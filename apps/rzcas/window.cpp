#include "window.hpp"

CasWindow::CasWindow()
{
    using Glib::ustring;

    set_resizable(false);
    set_title("Computer Algebra System");

    notebook.append_page(natural, "\xE2\x84\x95");
    notebook.append_page(integer, "\xE2\x84\xA4");
    notebook.append_page(rational, "\xE2\x84\x9A");
    notebook.append_page(polynomial, "\xE2\x84\x99");
    notebook.set_current_page(0);

    add(notebook);
    show_all();
}
