#include "rznumbers/rational.hpp"
#include "rznumbers/integer.hpp"
#include "rznumbers/natural.hpp"
#include <cctype>
#include <sstream>
#include <stdexcept>

Rational::Rational() : numerator("0"), denominator("1") {}

Rational::Rational(const Integer &numerator, const Natural &denominator)
    : numerator(numerator), denominator(denominator)
{
    this->reduce();
}

Rational::Rational(int numerator, unsigned int denominator)
    : numerator(numerator), denominator(denominator)
{
    this->reduce();
}

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
    is >> number.numerator;
    number.denominator = Natural(1);
    
    if ((is >> std::ws).peek() == '/') {
        is.get();
        is >> number.denominator;
    }

    if (!number.denominator) {
        throw std::runtime_error("denominator cannot be zero");
    }

    number.reduce();
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

    this->numerator = std::move(new_numerator);
    this->denominator = std::move(new_denominator);
    
    this->reduce();
    return *this;
}


Rational operator*(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res *= rhs;
}

Rational& Rational::operator*=(const Rational& rhs) {
    this->numerator *= std::move(rhs.numerator);
    this->denominator *= std::move(rhs.denominator);

    this->reduce();
    return *this;
}

Rational operator/(const Rational& lhs, const Rational& rhs) {
    Rational res(lhs);
    return res /= rhs;
}

Rational& Rational::operator/=(const Rational& rhs) {
    this->numerator *= Integer(rhs.denominator);
    this->denominator *= abs(rhs.numerator);
    this->reduce();
    if (rhs.numerator.positivity() == 1) {
        this->numerator *= Integer("-1");
    }
    return *this;
}

bool Rational::isInteger() {
    this->reduce();
    return denominator == Natural("1");
}

Rational::operator Integer() {
    reduce();
    if (denominator != Natural("1")) {
        throw std::logic_error("Cannot convert to integer: denominator is not 1.");
    }
    return numerator;
}

bool operator==(const Rational &lhs, const Rational &rhs)
{
    return lhs.numerator == rhs.numerator && lhs.denominator == rhs.denominator;
}

bool operator!=(const Rational &lhs, const Rational &rhs)
{
    return lhs.numerator != rhs.numerator || lhs.denominator != rhs.denominator;
}

int sign(const Rational &number)
{
    switch (number.numerator.positivity()) {
        case 1: return -1;
        case 2: return 1;
        default: return 0;
    }
}

Rational Rational::operator-()
{
    return Rational(-numerator, denominator);
}

Rational::operator bool() const
{
    return (bool)numerator;
}
