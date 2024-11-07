#include "../modes.hpp"

RationalMode::RationalMode() :
    b_reduce("red")
{
    b_reduce.signal_clicked().connect([this] { this->AddText("red"); });
    grid3.attach(b_reduce, 0, 0);
}
