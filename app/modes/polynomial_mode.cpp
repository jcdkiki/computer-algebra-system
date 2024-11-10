#include "polynomial_mode.hpp"
#include "../parsers/natural_parser.hpp"

PolynomialMode::PolynomialMode() :
    b_derivative("d/dx"), b_multiple_roots("nmr"), b_x("x"), b_power("^")
{
    b_derivative.signal_clicked().connect([this] { this->add_text("d/dx"); });
    b_x.signal_clicked().connect([this] { this->add_text("x"); });
    b_multiple_roots.signal_clicked().connect([this] { this->add_text("nmr"); });
    b_power.signal_clicked().connect([this] { this->add_text("^"); });

    grid3.attach(b_x, 0, 0);
    grid3.attach(b_derivative, 0, 1);
    grid3.attach(b_multiple_roots, 0, 2);
    grid3.attach(b_power, 0, 3);
}

Parser *PolynomialMode::create_parser(const char *str)
{
    return new NaturalParser(str);
}
