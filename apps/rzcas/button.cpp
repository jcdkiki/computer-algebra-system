#include "button.hpp"

CasButton::CasButton(Glib::ustring label) : Gtk::Button(label, true)
{
    set_relief(Gtk::RELIEF_NONE);
}

CasButton::CasButton()
{
    set_relief(Gtk::RELIEF_NONE);
}
