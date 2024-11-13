#include "integer_mode.hpp"
#include "../parsers/integer_parser.hpp"

IntegerMode::IntegerMode() : b_abs("abs")
{
    b_abs.signal_clicked().connect([this] { this->add_text("abs"); });
    grid3.attach(b_abs, 0, 2);
}

Parser *IntegerMode::create_parser(const char *str)
{
    return new IntegerParser(str);
}
