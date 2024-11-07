#ifndef CAS_WINDOW_HPP_
#define CAS_WINDOW_HPP_

#include <gtkmm.h>
#include "modes.hpp"

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
};

#endif
