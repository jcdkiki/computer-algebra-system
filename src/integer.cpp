#include "rznumbers/integer.hpp"
#include "rznumbers/natural.hpp"
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

Integer::Integer(int number)
{
    if (number < 0) {
        sign = true;
        natural = Natural(-number);
    }
    else {
        sign = false;
        natural = Natural(number);
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

    if ((is >> std::ws).peek() == '-') {
        number.sign = true;
        is.get();
    }

    is >> number.natural;

    number.fix_zero();
    return is;
}

void Integer::fix_zero()
{
    if(!natural){
        sign = false;
    }
}

Integer::operator bool() const
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

int Integer::positivity() const
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
bool Integer::operator==(const Integer &rhs) const{
    // знаки одинаковые и числа одинаковые
    return (sign == rhs.sign) && (natural == rhs.natural);
}

bool Integer::operator!=(const Integer &rhs) const{
    // первый не равен второму
    return !(*this == rhs);
}

bool Integer::operator>(const Integer &rhs) const{
    // если первый знак отрицательный и второй положительный
    if (sign && !rhs.sign)
        return false;
    
    // если первый положительный и второй отрицательный
    if (!sign && rhs.sign)
        return true;
    
    // если оба отрицательные
    if (sign && rhs.sign)
        return natural < rhs.natural;

    // если оба положительные
    return natural > rhs.natural;
}

bool Integer::operator<(const Integer &rhs) const {
    // если первый знак отрицательный и второй положительный
    if (sign && !rhs.sign)
        return true;
    
    // если первый положительный и второй отрицательный
    if (!sign && rhs.sign)
        return false;
    
    // если оба отрицательные
    if (sign && rhs.sign)
        return natural > rhs.natural;

    // если оба положительные
    return natural < rhs.natural;
}

bool Integer::operator>=(const Integer &rhs) const{
    // первый не меньше второго
    return !(*this < rhs);
}

bool Integer::operator<=(const Integer &rhs) const{
    // первый не больше второго
    return !(*this > rhs);
}

Natural abs(const Integer&number) {
    Natural res = number.natural;
    return res;
}

Integer Integer::operator*=(const Integer &number) {
    natural *= number.natural;
    sign = sign xor number.sign;
    fix_zero();
    return *this;
}

Integer operator * (const Integer &lhs, const Integer &rhs){
    Integer res(lhs);
    return res*=rhs;
}

Integer Integer::operator-() const{
    Integer new_int(natural);
    new_int.sign = !sign;
    new_int.fix_zero();
    return std::move(new_int);
}

Integer& Integer::operator/=(const Integer &number)
{
    sign = sign xor number.sign;

    bool flag = sign && *this % number;
    natural /= number.natural;
    
    if (flag) {
        natural++;
    }
    
    this->fix_zero();
    return *this;
}

Integer& Integer::operator%=(const Integer &number)
{
    natural %= number.natural;
    if(sign && *this){
        *this += number.natural;
    }
    this->fix_zero();
    return *this;
}


Integer operator/(const Integer &lhs, const Integer &rhs){
    Integer res(lhs);
    return res/=rhs;
}

Integer operator%(const Integer &lhs, const Integer &rhs){
    Integer res(lhs);
    return res%=rhs;
}

Integer::operator Natural() const{
    if(sign){
        throw std::runtime_error("cannot convert negative to natural");
    }
    return natural;
}
