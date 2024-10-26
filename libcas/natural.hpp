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

    friend bool cmp_with_zero(Natural n1);
    friend void inc(Natural& n);
    friend Natural add(Natural n1, Natural n2);
    
    Natural operator+(const Natural &number) const;
    static int cmp(const Natural &n1, const Natural &n2);

    bool operator==(const Natural &rhs) const;
    bool operator!=(const Natural &rhs) const;
    bool operator>(const Natural &rhs) const;
    bool operator<(const Natural &rhs) const;
    bool operator>=(const Natural &rhs) const;
    bool operator<=(const Natural &rhs) const;
};

std::ostream& operator<<(std::ostream& os, const Natural& number);
std::istream& operator>>(std::istream& is, Natural& number);

bool cmp_with_zero(Natural n1);
void inc(Natural& n);
Natural add(Natural n1, Natural n2);

#endif
