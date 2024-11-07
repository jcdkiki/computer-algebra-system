#include "../modes.hpp"

NaturalMode::NaturalMode() : b_gcd("gcd"), b_lcm("lcm")
{
    b_gcd.signal_clicked().connect([this] { this->AddText("gcd"); });
    b_lcm.signal_clicked().connect([this] { this->AddText("lcm"); });

    b_evaluate.signal_clicked().connect([this] {
        Natural res = this->parser.evaluate(entry.get_text().c_str());
        if (this->parser.get_error().size() > 0) {
            entry.set_text(this->parser.get_error());
        }
        else {
            entry.set_text(res.asString());
        }
    });

    grid3.attach(b_gcd, 0, 0);
    grid3.attach(b_lcm, 0, 1);
}
