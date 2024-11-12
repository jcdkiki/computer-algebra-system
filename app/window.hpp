#ifndef CAS_WINDOW_HPP_
#define CAS_WINDOW_HPP_

#include <gtkmm.h>
#include "modes/natural_mode.hpp"
#include "modes/integer_mode.hpp"
#include "modes/rational_mode.hpp"
#include "modes/polynomial_mode.hpp"

class CasWindow : public Gtk::Window
{
    Gtk::Notebook notebook;

    NaturalMode natural;
    IntegerMode integer;
    RationalMode rational;
    PolynomialMode polynomial;

public:
    CasWindow();
    ~CasWindow() = default;
    
    bool key_controller_cb(guint keyval, guint, Gdk::ModifierType state);
};

#endif
