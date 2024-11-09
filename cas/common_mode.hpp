#ifndef CAS_COMMON_MODE_HPP_
#define CAS_COMMON_MODE_HPP_

#include <gtkmm.h>
#include <gtkmm/widget.h>
#include "button.hpp"
#include "parser.hpp"

class CommonMode : public Gtk::Box {
protected:
    Gtk::Box box;
    Gtk::Entry entry;
    Gtk::TextView status;

    Gtk::Grid grid1;
    CasButton b_digits09[9];
    CasButton b_zero;
    CasButton b_evaluate;
    CasButton b_erase;

    Gtk::Separator separator;

    Gtk::Grid grid2;
    CasButton b_plus;
    CasButton b_minus;
    CasButton b_mul;
    CasButton b_div;
    CasButton b_mod;
    CasButton b_lparen;
    CasButton b_rparen;
    CasButton b_comma;

    Gtk::Separator separator2;
    Gtk::Grid grid3;

    void add_text(Glib::ustring str);
    void set_status(const std::string &str);
    void erase();
    void evaluate();

    virtual Parser *create_parser(const char *str) = 0;

public:
    CommonMode();
};

#endif
