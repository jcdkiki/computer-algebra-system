#include "integer.hpp"
#include <cctype>

Integer::Integer() : sign(false), natural(Natural()) {}

Integer::Integer(const char *str) : sign(false)
{
    if (*str == '-') {
        sign = true;
        str++;
    }
    
    natural = Natural(str);
    if (!natural) {
        sign = false;
    }
}

Integer::Integer(const Natural &number) : sign(false), natural(number) {}

std::string Integer::asString()
{
    std::string res;
    if (sign) {
        res += "-";
    }
    res += natural.asString();
    return res;
}

std::ostream& operator<<(std::ostream& os, const Integer& number)
{
    if (number.sign) {
        os << '-';
    }
    os << number.natural;
    return os;
}

std::istream& operator>>(std::istream& is, Integer& number)
{
    number.sign = false;
    char c;

    while (true) {
        c = is.get();
        if (is.fail() || !std::isspace(c))
            break;
    }
    
    if (c == '-') {
        number.sign = true;
    }
    else {
        is.unget();
    }

    is >> number.natural;

    if (!number.natural) {
        number.sign = false;
    }

    return is;
}

Integer::operator bool()
{
    return bool(natural);
}

int Integer::positivity(){
    if (sign){
        return 1; // number < 0
    }
    if (natural){
        return 2; // number > 0
    }
    return 0; //number == 0
}