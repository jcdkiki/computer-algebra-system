#include "rational.hpp"
#include "natural.hpp"
#include <sstream>

Rational::Rational() : numerator("0"), denominator("1") {}

Rational::Rational(const char *str)
{
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

std::string Rational::asString()
{
    return numerator.asString() + '/' + denominator.asString();
}

std::ostream& operator<<(std::ostream& os, const Rational& number)
{
    os << number.numerator << '/' << number.denominator;
    return os;
}

std::istream& operator>>(std::istream& is, Rational& number)
{
    char c;
    is >> number.numerator;
    
    is >> c;
    if (c != '/') {
        is.unget();
        number.numerator = Integer("0");       // indeterminate form
        number.denominator = Natural("0");     // TODO: change later??????
    }
    
    is >> number.denominator;
    return is;
}
