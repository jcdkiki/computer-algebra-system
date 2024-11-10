#include "button.hpp"

CasButton::CasButton(Glib::ustring label) : Gtk::Button(label, true)
{
    set_has_frame(false);
}

CasButton::CasButton()
{
    set_has_frame(false);
}
