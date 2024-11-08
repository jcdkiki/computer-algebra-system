#include "rational.hpp"
#include "natural.hpp"
#include <sstream>
#include <stdexcept>

Rational::Rational() : numerator("0"), denominator("1") {}

Rational::Rational(const char *str)
{
    std::stringstream ss;
    ss << str;
    ss >> *this;
}

std::string Rational::asString()
{
    if (denominator == Natural("1")) {
        return numerator.asString();
    }
    return numerator.asString() + '/' + denominator.asString();
}

std::ostream& operator<<(std::ostream& os, const Rational& number)
{
    if (number.denominator == Natural("1")) {
        return (os << number.numerator);
    }
    return (os << number.numerator << '/' << number.denominator);
}

std::istream& operator>>(std::istream& is, Rational& number)
{
    char c;
    is >> number.numerator;
    
    is >> c;
    if (c != '/') {
        is.unget();
        number.denominator = Natural("1");
        return is;
    }
    
    is >> number.denominator;

    if (!number.denominator) {
        throw std::runtime_error("denominator cannot be zero");
    }
    return is;
}

Natural Rational::greatest_common_divisor(const Integer& numerator, const Natural& denominator) {
    Natural natur_numerator = abs(numerator);
    Natural natur_denominator = denominator;

    while (natur_denominator != 0) {
        Natural temp = natur_denominator;
        natur_denominator = natur_numerator % natur_denominator;
        natur_numerator = temp;
    }

    return natur_numerator;
}

void Rational::reduce() {
    Natural common_divisor = greatest_common_divisor(numerator, denominator);
    if (!numerator) {
        denominator = Natural("1");
        return;
    }
    Integer del_nem(common_divisor);
    Natural del_den(common_divisor);
    numerator = numerator / del_nem;
    denominator = denominator / del_den;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res += rhs;
}

Rational& Rational::operator+=(const Rational& rhs) {

    Integer new_numerator = this->numerator * Integer(rhs.denominator) + rhs.numerator * Integer(this->denominator);
    Natural new_denominator = this->denominator * rhs.denominator;

    this->numerator = new_numerator;
    this->denominator = new_denominator;

    this->reduce();

    return *this;
}

Rational operator-(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res -= rhs;
}

Rational& Rational::operator-=(const Rational& rhs) {
    Integer new_numerator = this->numerator * Integer(rhs.denominator) - rhs.numerator * Integer(this->denominator);
    Natural new_denominator = this->denominator * rhs.denominator;

    this->numerator = new_numerator;
    this->denominator = new_denominator;
    
    this->reduce();
    return *this;
}