#ifndef CAS_NUMBERS_RATIONAL_HPP_
#define CAS_NUMBERS_RATIONAL_HPP_

#include "natural.hpp"
#include "integer.hpp"

class Rational {
    Integer numerator;
    Natural denominator;
public:
    Rational();
    explicit Rational(const char *str);
    std::string asString();

    friend std::ostream& operator<<(std::ostream& os, const Rational& number);
    friend std::istream& operator>>(std::istream& is, Rational& number);
};

std::ostream& operator<<(std::ostream& os, const Rational& number);
std::istream& operator>>(std::istream& is, Rational& number);

#endif
