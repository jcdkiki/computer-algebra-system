#include "integer.hpp"
#include <iostream>
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

Integer& Integer::operator++(){
    natural++;
    return *this;
}

Integer Integer::operator++(int){
    Integer old = *this;
    natural++;
    return old;
}

Integer& Integer::operator+=(const Integer &n){
    if(sign == n.sign){
        natural += n.natural;
        return *this;
    }
    if(natural > n.natural){
        natural -= n.natural;
        return *this;
    }
    else{
        Natural temp = n.natural;
        sign = n.sign;
        temp -= natural;
        natural = temp;
        return *this;
    }
}


Integer operator+(const Integer &lhs, const Integer &rhs)
{
    Integer res(lhs);
    return res += rhs;
}