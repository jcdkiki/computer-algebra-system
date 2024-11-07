#include <gtkmm.h>
#include "button.hpp"

class CommonMode : public Gtk::Box {
protected:
    Gtk::EditableLabel entry;
    Gtk::Box box;
    Gtk::Grid grid1;
    CasButton b_digits09[9];
    CasButton b_zero;
    CasButton b_evaluate;

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

    void AddText(Glib::ustring str)
    {
        entry.set_text(entry.get_text() + str);
    }

public:
    CommonMode() :
        b_zero("0"), b_evaluate("="), b_plus("+"), b_minus("\xE2\x88\x92"), b_mul("\xC3\x97"),
        b_div("\xC3\xB7"), b_mod("%"), b_lparen("("), b_rparen(")"), b_comma(",")
    {
        using Glib::ustring;

        set_spacing(3);
        set_orientation(Gtk::Orientation::VERTICAL);

        grid1.set_column_homogeneous();
        grid2.set_row_homogeneous();

        for (int i = 0; i < 9; i++) {
            ustring label = ustring::format(i + 1);
            b_digits09[i].set_label(label);
            b_digits09[i].signal_clicked().connect([this, label] { this->AddText(label); });
            grid1.attach(b_digits09[i], i % 3, i / 3);
        }

        b_zero.signal_clicked().connect([this] { this->AddText("0"); });
        b_plus.signal_clicked().connect([this] { this->AddText("+"); });
        b_minus.signal_clicked().connect([this] { this->AddText("-"); });
        b_mul.signal_clicked().connect([this] { this->AddText("*"); });
        b_div.signal_clicked().connect([this] { this->AddText("/"); });
        b_mod.signal_clicked().connect([this] { this->AddText("%"); });
        b_lparen.signal_clicked().connect([this] { this->AddText("("); });
        b_rparen.signal_clicked().connect([this] { this->AddText(")"); });
        b_comma.signal_clicked().connect([this] { this->AddText(","); });

        grid1.attach(b_zero, 1, 3);
        grid1.attach(b_evaluate, 0, 3);
        
        grid2.attach(b_plus, 0, 0);
        grid2.attach(b_minus, 1, 0);
        grid2.attach(b_mul, 0, 1);
        grid2.attach(b_div, 1, 1);
        grid2.attach(b_lparen, 0, 2);
        grid2.attach(b_rparen, 1, 2);
        grid2.attach(b_mod, 0, 3);
        grid2.attach(b_comma, 1, 3);

        box.set_orientation(Gtk::Orientation::HORIZONTAL);
        box.set_spacing(3);
        box.append(grid1);
        box.append(separator);
        box.append(grid2);
        box.append(separator2);
        box.append(grid3);
        
        entry.set_halign(Gtk::Align::START);
        
        append(entry);
        append(box);
    }
};
