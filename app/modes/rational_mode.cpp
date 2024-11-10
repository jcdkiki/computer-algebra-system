#include "rational_mode.hpp"
#include "../parsers/natural_parser.hpp"

RationalMode::RationalMode() :
    b_reduce("red")
{
    b_reduce.signal_clicked().connect([this] { this->add_text("red"); });
    grid3.attach(b_reduce, 0, 0);
}

Parser *RationalMode::create_parser(const char *str)
{
    return new NaturalParser(str);
}
