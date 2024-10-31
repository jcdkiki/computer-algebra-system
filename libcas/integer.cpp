#include "integer.hpp"
#include <algorithm>
#include <cctype>

Integer::Integer() : sign(false), digits(1, 0) {}

Integer::Integer(const char *str)
{
    if (*str == '-') {
        sign = true;
        str++;
    }

    while (std::isdigit(*str)) {
        digits.push_back(*str - '0');
        str++;
    }

    if (digits.size() == 0) {
        digits.push_back(0);
    }

    std::reverse(digits.begin(), digits.end());

    if (isZero()) {
        sign = false;
    }
}

std::string Integer::asString()
{
    std::string res;
    if (sign) {
        res += "-";
    }
    
    for (ssize_t i = digits.size() - 1; i >= 0; --i) {
        res += (char)(digits[i] + '0');
    }
    return res;
}

std::ostream& operator<<(std::ostream& os, const Integer& number)
{
    if (number.sign) {
        os << '-';
    }

    for (ssize_t i = number.digits.size() - 1; i >= 0; --i) {
        os << (char)(number.digits[i] + '0');
    }
    return os;
}

std::istream& operator>>(std::istream& is, Integer& number)
{
    char c;
    number.digits.resize(0);

    while (true) {
        c = is.get();
        if (is.fail() || !std::isspace(c))
            break;
    }

    if (c == '-') {
        number.sign = true;
        c = is.get();
    }

    while (true) {
        if (is.fail() || !std::isdigit(c))
            break;
        
        number.digits.push_back(c - '0');
        c = is.get();
    }

    is.unget();

    if (number.digits.size() == 0) {
        number.digits.push_back(0);
    }

    std::reverse(number.digits.begin(), number.digits.end());

    if (number.isZero()) {
        number.sign = false;
    }

    return is;
}

bool Integer::isZero()
{
    return (digits.size() == 1) && (digits[0] == 0);
}
