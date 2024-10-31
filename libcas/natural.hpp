#ifndef CAS_NUMBERS_NATURAL_HPP_
#define CAS_NUMBERS_NATURAL_HPP_

#include <vector>
#include <ostream>
#include <istream>
#include <string>

class Natural {
    using Digit = char;
    std::vector<Digit> digits;

    void strip();

public:
    constexpr static int BASE = 10;

    Natural();
    explicit Natural(const char *str);
    std::string asString();

    friend std::ostream& operator<<(std::ostream& os, const Natural& number);
    friend std::istream& operator>>(std::istream& is, Natural& number);

    
    Natural operator+(const Natural &number) const;
    Natural& operator+=(const Natural &n);
    Natural& operator++();
    Natural operator++(int);
    static int cmp(const Natural &n1, const Natural &n2);
    operator bool();

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
