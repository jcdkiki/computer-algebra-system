#include "../modes.hpp"

PolynomialMode::PolynomialMode() :
    b_derivative("d/dx"), b_multiple_roots("nmr"), b_x("x"), b_power("^")
{
    b_derivative.signal_clicked().connect([this] { this->AddText("d/dx"); });
    b_x.signal_clicked().connect([this] { this->AddText("x"); });
    b_multiple_roots.signal_clicked().connect([this] { this->AddText("nmr"); });
    b_power.signal_clicked().connect([this] { this->AddText("^"); });

    grid3.attach(b_x, 0, 0);
    grid3.attach(b_derivative, 0, 1);
    grid3.attach(b_multiple_roots, 0, 2);
    grid3.attach(b_power, 0, 3);
}
