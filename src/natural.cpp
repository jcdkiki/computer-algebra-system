#include "natural.hpp"
#include <algorithm>
#include <cctype>

Natural::Natural() : digits(1, 0) {}

std::ostream& operator<<(std::ostream& os, const Natural& number)
{
    for (ssize_t i = number.digits.size() - 1; i >= 0; i--) {
        os << (char)(number.digits[i] + '0');
    }
    return os;
}

std::istream& operator>>(std::istream& is, Natural& number)
{
    char c;
    number.digits.resize(0);

    while (true) {
        c = is.get();
        if (is.fail() || !std::isspace(c))
            break;
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
    return is;
}
