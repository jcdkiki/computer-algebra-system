#ifndef CAS_BUTTON_HPP_
#define CAS_BUTTON_HPP_

#include <gtkmm.h>

class CasButton : public Gtk::Button {
public:
    CasButton(Glib::ustring label);
    CasButton();
};

#endif
