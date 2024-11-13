#include "polynomial_mode.hpp"
#include "../parsers/polynomial_parser.hpp"

PolynomialMode::PolynomialMode() :
    b_derivative("d/dx"), b_nmr("nmr"), b_factorize("fac"), b_x("x"), b_power("^")
{
    b_derivative.signal_clicked().connect([this] { this->add_text("d/dx"); });
    b_x.signal_clicked().connect([this] { this->add_text("x"); });
    b_nmr.signal_clicked().connect([this] { this->add_text("nmr"); });
    b_power.signal_clicked().connect([this] { this->add_text("^"); });
    b_factorize.signal_clicked().connect([this] { this->add_text("fac"); });

    grid3.attach(b_x, 0, 0);
    grid3.attach(b_derivative, 0, 1);
    grid3.attach(b_nmr, 0, 2);
    grid3.attach(b_power, 0, 3);
    grid3.attach(b_factorize, 1, 0);
}

Parser *PolynomialMode::create_parser(const char *str)
{
    return new PolynomialParser(str);
}
