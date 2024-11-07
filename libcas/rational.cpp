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

Integer Rational::gcd_recursive(const Integer& numerator, const Integer& denominator) {
    Natural natur_numerator = abs(numerator);
    Natural natur_denominator = abs(denominator);

    if (natur_numerator % natur_denominator == 0)
        return natur_denominator;
    if (natur_denominator % natur_numerator == 0)
        return natur_numerator;
    if (natur_numerator > natur_denominator)
        return gcd_recursive(natur_numerator % natur_denominator, natur_denominator);
    return gcd_recursive(natur_numerator, natur_denominator % natur_numerator);
}

const char* Rational::greatest_common_divisor(const Integer& numerator, const Natural& denominator) {
    Integer gcd_result = gcd_recursive(numerator, denominator);
    std::string result_str = gcd_result.asString();
    char* cstr = new char[result_str.length() + 1];
    std::strcpy(cstr, result_str.c_str());
    return cstr; 
}

void Rational::reduce() {
    const char* common_divisor = greatest_common_divisor(numerator, denominator);
    if(numerator.asString() == "0") {
        denominator = denominator / denominator;
        return;
    }
    Integer del_nem(common_divisor);
    Natural del_den(common_divisor);
    numerator = numerator / del_nem;
    denominator = denominator / del_den;
}

Rational& Rational::operator+(const Rational& other) {
    Rational temp = other; 
    Integer new_denominator = convert_denominator_to_integer(temp);

    numerator = numerator * new_denominator + temp.numerator * Integer(denominator);
    denominator = denominator * temp.denominator;
    reduce();
    return *this;
}