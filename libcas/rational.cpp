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

void Rational::reduce() {
    if (!numerator) {
        denominator = Natural("1");
        return;
    }
    Natural common_divisor = greatCommDiv( abs(numerator), denominator);
    numerator /= Integer(common_divisor);
    denominator /= common_divisor;
}

Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res += rhs;
}

Rational& Rational::operator+=(const Rational& rhs) {

    Integer new_numerator = this->numerator * Integer(rhs.denominator) + rhs.numerator * Integer(this->denominator);
    Natural new_denominator = this->denominator * rhs.denominator;

    this->numerator = std::move(new_numerator);
    this->denominator = std::move(new_denominator);

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


Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res *= rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
    numerator = numerator * rhs.numerator;
    denominator = denominator * rhs.denominator;

    reduce();
    return *this;
}