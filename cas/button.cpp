#include "button.hpp"
#include <glibmm/refptr.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/enums.h>

CasButton::CasButton(Glib::ustring label) : Gtk::Button(label, true)
{
    this->set_relief(Gtk::RELIEF_NONE);
}

CasButton::CasButton()
{
    this->set_relief(Gtk::RELIEF_NONE);
}
