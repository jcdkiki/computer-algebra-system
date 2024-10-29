#ifndef CAS_NUMBERS_NATURAL_HPP_
#define CAS_NUMBERS_NATURAL_HPP_

#include <vector>
#include <ostream>
#include <istream>

class Natural {
    using Digit = char;
    std::vector<Digit> digits;
public:
    constexpr static int BASE = 10;

    Natural();

    friend std::ostream& operator<<(std::ostream& os, const Natural& number);
    friend std::istream& operator>>(std::istream& is, Natural& number);

    
    Natural operator+(const Natural &number) const;
    Natural& operator+=(const Natural &n);
    Natural& operator++();
    Natural operator++(int);
    static int cmp(const Natural &n1, const Natural &n2);
    friend bool cmp_with_zero(Natural n1);

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

#endif
