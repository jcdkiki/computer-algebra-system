#include "natural_mode.hpp"
#include "../parsers/natural_parser.hpp"

NaturalMode::NaturalMode() : b_gcd("gcd"), b_lcm("lcm")
{
    b_gcd.signal_clicked().connect([this] { this->add_text("gcd"); });
    b_lcm.signal_clicked().connect([this] { this->add_text("lcm"); });

    grid3.attach(b_gcd, 0, 0);
    grid3.attach(b_lcm, 0, 1);
}

Parser *NaturalMode::create_parser(const char *str)
{
    return new NaturalParser(str);
}
