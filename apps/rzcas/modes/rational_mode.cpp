#include "rational_mode.hpp"
#include "../parsers/rational_parser.hpp"

RationalMode::RationalMode() :
    b_inverse("inv")
{
    b_inverse.signal_clicked().connect([this] { this->add_text("inv"); });
    grid3.attach(b_inverse, 0, 0);
    grid2.remove(b_mod);
}

Parser *RationalMode::create_parser(const char *str)
{
    return new RationalParser(str);
}
