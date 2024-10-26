#ifndef CAS_NUMBERS_NATURAL_HPP_
#define CAS_NUMBERS_NATURAL_HPP_

#include <vector>
#include <ostream>
#include <istream>

class Natural {
    using Digit = unsigned char;
    std::vector<Digit> digits;
public:
    Natural();

    friend std::ostream& operator<<(std::ostream& os, const Natural& number);
    friend std::istream& operator>>(std::istream& is, Natural& number);

    friend int cmp(Natural n1, Natural n2);
    friend bool cmp_with_zero(Natural n1);
    friend void inc(Natural& n);
};

std::ostream& operator<<(std::ostream& os, const Natural& number);
std::istream& operator>>(std::istream& is, Natural& number);

int cmp(Natural n1, Natural n2);
bool cmp_with_zero(Natural n1);
void inc(Natural& n);
#endif
