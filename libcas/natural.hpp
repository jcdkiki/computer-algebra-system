#ifndef CAS_NUMBERS_NATURAL_HPP_
#define CAS_NUMBERS_NATURAL_HPP_

#include <vector>
#include <ostream>
#include <istream>

class Natural {
    using Digit = char;
    std::vector<Digit> digits;
public:
    static constexpr int BASE = 10;

    Natural();
    Natural(std::vector<Digit> digits);

    friend std::ostream& operator<<(std::ostream& os, const Natural& number);
    friend std::istream& operator>>(std::istream& is, Natural& number);

    Natural operator+(const Natural &number) const;
    Natural operator-(const Natural &number) const;
    static int cmp(const Natural &n1, const Natural &n2);
    friend Natural sub(Natural n1, Natural n2);

    bool operator==(const Natural &rhs) const;
    bool operator!=(const Natural &rhs) const;
    bool operator>(const Natural &rhs) const;
    bool operator<(const Natural &rhs) const;
    bool operator>=(const Natural &rhs) const;
    bool operator<=(const Natural &rhs) const;
};

Natural sub(Natural n1, Natural n2);
std::ostream& operator<<(std::ostream& os, const Natural& number);
std::istream& operator>>(std::istream& is, Natural& number);

#endif
