#include "common_mode.hpp"
#include <gtk-4.0/gtk/gtk.h>
#include <gtk/gtk.h>
#include <gtkmm/enums.h>

void CommonMode::add_text(Glib::ustring str)
{
    int position;
    entry.insert_text(str, str.size(), position);
}

void CommonMode::set_status(const std::string &str)
{
    status.get_buffer()->set_text(str);
    status.set_resize_mode(Gtk::ResizeMode::RESIZE_IMMEDIATE);
    status.set_size_request(300, -1);
    status.set_tooltip_text(str);
}

void CommonMode::erase()
{
    entry.delete_text(entry.get_chars(0, -1).size() - 1, -1);
}

void CommonMode::evaluate()
{
    auto text = entry.get_chars(0, -1);
    std::unique_ptr<Parser> parser(this->create_parser(text.c_str()));

    try {
        std::string res = parser->evaluate();
        entry.set_text(res);
        set_status("OK");
    }
    catch (ParserException &e) {
        set_status(std::string("Syntax error: ") + e.what().data());
    }
    catch (std::runtime_error &e) {
        set_status(std::string("Math error: ") + e.what());
    }
}

#define CAS_SET_MARGIN(object, margin) \
    object.set_margin_bottom(margin); \
    object.set_margin_top(margin); \
    object.set_margin_left(margin); \
    object.set_margin_right(margin); \
    object.set_margin_start(margin); \
    object.set_margin_end(margin)

CommonMode::CommonMode() :
    b_zero("0"), b_evaluate("="), b_plus("+"), b_minus("\xE2\x88\x92"), b_mul("\xC3\x97"),
    b_div("\xC3\xB7"), b_mod("%"), b_lparen("("), b_rparen(")"), b_comma(","),
    b_erase("\xE2\x8C\xAB")
{
    using Glib::ustring;

    this->set_spacing(6);
    CAS_SET_MARGIN((*this), 6);
    this->set_orientation(Gtk::Orientation::ORIENTATION_VERTICAL);

    grid1.set_column_homogeneous(true);
    grid2.set_row_homogeneous(true);

    for (int i = 0; i < 9; i++) {
        ustring label = ustring::format(i + 1);
        b_digits09[i].set_label(label);
        b_digits09[i].signal_clicked().connect([this, label] { this->add_text(label); });
        grid1.attach(b_digits09[i], i % 3, i / 3);
    }

    b_zero.signal_clicked().connect([this] { this->add_text("0"); });
    b_plus.signal_clicked().connect([this] { this->add_text("+"); });
    b_minus.signal_clicked().connect([this] { this->add_text("-"); });
    b_mul.signal_clicked().connect([this] { this->add_text("*"); });
    b_div.signal_clicked().connect([this] { this->add_text("/"); });
    b_mod.signal_clicked().connect([this] { this->add_text("%"); });
    b_lparen.signal_clicked().connect([this] { this->add_text("("); });
    b_rparen.signal_clicked().connect([this] { this->add_text(")"); });
    b_comma.signal_clicked().connect([this] { this->add_text(","); });
    b_erase.signal_clicked().connect([this] { this->erase(); });

    grid1.attach(b_evaluate, 0, 3);
    grid1.attach(b_zero, 1, 3);
    grid1.attach(b_erase, 2, 3);
    
    grid2.attach(b_plus, 0, 0);
    grid2.attach(b_minus, 1, 0);
    grid2.attach(b_mul, 0, 1);
    grid2.attach(b_div, 1, 1);
    grid2.attach(b_lparen, 0, 2);
    grid2.attach(b_rparen, 1, 2);
    grid2.attach(b_mod, 0, 3);
    grid2.attach(b_comma, 1, 3);

    box.set_orientation(Gtk::Orientation::ORIENTATION_HORIZONTAL);
    box.set_spacing(3);
    box.add(grid1);
    box.add(separator);
    box.add(grid2);
    box.add(separator2);
    box.add(grid3);
    
    entry.set_halign(Gtk::Align::ALIGN_START);
    
    status.set_editable(false);
    status.set_buffer(Gtk::TextBuffer::create());
    status.get_buffer()->set_text("Welcome to Computer Algebra System");
    status.set_wrap_mode(Gtk::WRAP_WORD);

    CAS_SET_MARGIN(entry, 6);

    this->add(entry);
    this->add(box);
    this->add(status);

    entry.set_size_request(300, -1);
}
