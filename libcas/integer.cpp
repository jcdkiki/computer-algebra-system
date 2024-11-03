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
    this->fix_zero();
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

void Integer::fix_zero()
{
    if(!natural){
        sign = false;
    }
}

Integer::operator bool()
{
    return bool(natural);
}

Integer& Integer::operator++(){
    if(sign){
        natural--;
    }
    else{
        natural++;
    }
    this->fix_zero();
    return *this;
}

Integer Integer::operator++(int){
    Integer old = *this;
    ++(*this);
    return old;
}

Integer& Integer::operator+=(const Integer &n){
    if(sign == n.sign){
        natural += n.natural;
        return *this;
    }
    if(natural >= n.natural){
        natural -= n.natural;
        this->fix_zero();
        return *this;
    }
    else{
        natural = n.natural - natural;
        sign = n.sign;
        return *this;
    }
}


Integer operator+(const Integer &lhs, const Integer &rhs)
{
    Integer res(lhs);
    return res += rhs;
}

int Integer::positivity()
{
    if (sign){
        return 1; // number < 0
    }
    if (natural){
        return 2; // number > 0
    }
    return 0; //number == 0
}

Integer& Integer::operator--(){
    if(sign){
        natural++;
    }
    else{
        natural--;
    }
    this->fix_zero();
    return *this;
}

Integer Integer::operator--(int){
    Integer old = *this;
    --(*this);
    return old;
}

Integer& Integer::operator-=(const Integer &n){
    if(sign != n.sign){
        natural += n.natural;
        return *this;
    }
    if(natural >= n.natural){
        natural -= n.natural;
        this->fix_zero();
        return *this;
    }
    else{
        natural = n.natural - natural;
        sign = !sign;
        return *this;
    }
}

Integer operator-(const Integer &lhs, const Integer &rhs)
{
    Integer res(lhs);
    return res -= rhs;
}
