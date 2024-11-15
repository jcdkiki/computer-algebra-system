#include "rznumbers/natural.hpp"

#include <algorithm>
#include <ios>
#include <iostream>
#include <cctype>
#include <stdexcept>

Natural::Natural() : digits(1, 0) {}

Natural::Natural(unsigned int number)
{
    do {
        digits.push_back(number % 10);
        number /= 10;
    } while (number != 0);
}

Natural::Natural(const char *str)
{
    while (std::isdigit(*str)) {
        digits.push_back(*str - '0');
        str++;
    }

    if (digits.size() == 0) {
        digits.push_back(0);
    }

    std::reverse(digits.begin(), digits.end());
    this->strip();
}

void Natural::strip()
{
    while (digits.size() > 1 && digits.back() == 0) {
        digits.pop_back();
    }
}

std::ostream& operator<<(std::ostream& os, const Natural& number)
{
    for (ssize_t i = number.digits.size() - 1; i >= 0; --i) {
        os << (char)(number.digits[i] + '0');
    }
    return os;
}

std::string Natural::asString()
{
    std::string res;
    for (ssize_t i = digits.size() - 1; i >= 0; --i) {
        res += (char)(digits[i] + '0');
    }
    return res;
}

std::istream& operator>>(std::istream& is, Natural& number)
{   
    number.digits.resize(0);

    is >> std::ws;
    while (true) {
        char c = is.peek();
        if (is.eof() || is.fail() || !std::isdigit(c)) {
            break;
        }
        
        is.get();
        number.digits.push_back(c - '0');
    }

    if (number.digits.size() == 0) {
        number.digits.push_back(0);
        throw std::runtime_error("number cannot be empty");
    }

    std::reverse(number.digits.begin(), number.digits.end());
    number.strip();
    
    return is;
}

int Natural::cmp(const Natural &n1, const Natural &n2) {
    if (n1.digits.size() > n2.digits.size()) {
        return 2; // n1 > n2
    }

    if (n1.digits.size() < n2.digits.size()) {
        return 1; // n1 < n2
    }

    for (ssize_t i = n1.digits.size() - 1; i >= 0; --i) {
        if (n1.digits[i] > n2.digits[i]) {
            return 2; // n1 > n2
        } 
        else if (n1.digits[i] < n2.digits[i]) {
            return 1; // n1 < n2
        }
    }

    return 0; // n1 == n2
}

Natural getDivDigitInPower(const Natural &lhs, const Natural &rhs){
    if (lhs < rhs){
        throw std::runtime_error("cannot div from a smaller number");
    }

    if (!rhs){
        throw std::runtime_error("cannot div from a null");
    }

    size_t k = lhs.digits.size() - rhs.digits.size();
    if (lhs < (rhs << k)){
        k -= 1;
    }

    Natural sub = rhs << k;
    Natural minuend = lhs;
    Natural res("0");
    
    while (minuend >= sub){
        res++;
        minuend -= sub;
    }

    return res << k;
}

Natural& Natural::operator/=(const Natural &number) {
    if(!number){
        throw std::runtime_error("cannot div from a null");
    }

    Natural current = *this;
    *this = Natural();
    
    Natural part;
    while (current >= number){
        part = getDivDigitInPower(current, number);
        *this += part;
        current -= part * number;
    }
    
    return *this;
}

Natural& Natural::operator%=(const Natural &number) {
    if(!number){
        throw std::runtime_error("cannot div from a null");
    }
    *this -= (*this / number) * number;
    return *this;
}

Natural operator%(const Natural &lhs, const Natural &rhs) {
    Natural res(lhs);
    return res %= rhs;
}

Natural operator/(const Natural &lhs, const Natural &rhs) {
    Natural res(lhs);
    return res /= rhs;
}

Natural operator-(const Natural &lhs, const Natural &rhs) {
    Natural res(lhs);
    return res -= rhs;
}

Natural& Natural::operator-=(const Natural &number) {
    if (number > *this) {
        throw std::runtime_error("cannot sub from a smaller number");
    }

    Natural::Digit carry = 0;
    for (size_t i = 0; i < this->digits.size() || carry; ++i) {
        this->digits[i] -= carry + ((i < number.digits.size()) ? number.digits[i]: 0);
        carry = this->digits[i] < 0;
        if (carry) this->digits[i] += Natural::BASE;
    }

    this->strip();
    return *this;
}

Natural& Natural::operator--() {
    if (!(*this)) {
        throw std::runtime_error("cannot decrement zero");
    }

    Natural::Digit carry = 1;
    for (size_t i = 0; i < this->digits.size() || carry; ++i) {
        this->digits[i] -= carry;
        carry = this->digits[i] < 0;
        if (carry) this->digits[i] += Natural::BASE;
    }

    // strip insignificant zeros
    while (this->digits.size() > 1 && this->digits.back() == 0) {
        this->digits.pop_back();
    }

    return *this;
}

Natural Natural::operator--(int) {
    Natural old = *this;
    operator--();
    return old;
}

bool Natural::operator==(const Natural &rhs) const
{
    return (Natural::cmp(*this, rhs) == 0);
}

bool Natural::operator!=(const Natural &rhs) const
{
    return (Natural::cmp(*this, rhs) != 0);
}

bool Natural::operator>(const Natural &rhs) const
{
    return (Natural::cmp(*this, rhs) == 2);
}

bool Natural::operator<(const Natural &rhs) const
{
    return (Natural::cmp(*this, rhs) == 1);
}

bool Natural::operator>=(const Natural &rhs) const
{
    int res = Natural::cmp(*this, rhs);
    return (res == 2) || (res == 0);
}

bool Natural::operator<=(const Natural &rhs) const
{
    int res = Natural::cmp(*this, rhs);
    return (res == 1) || (res == 0);
}

Natural Natural::operator*(const Natural::Digit& digit) const {
    Natural res(*this);
    return res *= digit;
}

Natural &Natural::operator*=(const Natural::Digit& digit) {
    Natural::Digit carry = 0;
    for (size_t i = 0; i < this->digits.size() || carry; ++i) {
        if (i == this->digits.size()) {
            this->digits.push_back(0);
        }

        size_t temp = carry + this->digits[i] * digit;

        this->digits[i] = temp % Natural::BASE;
        carry = temp / Natural::BASE;
    }

    this->strip();
    return *this;
}

Natural &Natural::mul_by_10_in_k(size_t k) {
    this->digits.insert(this->digits.begin(), k, 0);
    this->strip();
    return *this;
}

Natural Natural::operator<<(size_t k) const {
    Natural res(*this);
    return res <<= k;
}

Natural &Natural::operator<<=(size_t k) {
    this->mul_by_10_in_k(k);
    return *this;
}

Natural operator*(const Natural &lhs, const Natural &rhs) {
    Natural::Digit carry = 0;
    Natural res;
    res.digits.resize(lhs.digits.size() + rhs.digits.size());

    for (size_t i = 0; i < lhs.digits.size(); ++i) {
        for (size_t j = 0; j < rhs.digits.size() || carry; ++j) {
            size_t temp = res.digits[i + j] + lhs.digits[i] * (j < rhs.digits.size() ? rhs.digits[j]: 0) + carry;
            res.digits[i + j] = temp % Natural::BASE;
            carry = temp / Natural::BASE;
        }
    }

    res.strip();
    return res;
}

Natural Natural::operator*=(const Natural &number) {
    *this = *this * number;
    return *this;
}

Natural operator+(const Natural &lhs, const Natural &rhs) {
    Natural res(lhs);
    return res += rhs;
}

Natural& Natural::operator+=(const Natural &number) {
    Natural::Digit carry = 0;

    for (size_t i = 0; i < std::max(this->digits.size(), number.digits.size()) || carry; ++i) {
        if (i == this->digits.size()) {
            this->digits.push_back (0);
        }
        this->digits[i] += carry + (i < number.digits.size() ? number.digits[i] : 0);
        carry = this->digits[i] >= Natural::BASE;
        if (carry) this->digits[i] -= Natural::BASE;
    }

    return *this;
}

Natural& Natural::operator++() {
    Natural::Digit carry = 1;

    for (size_t i = 0; i < this->digits.size() || carry; ++i) {
        if (i == this->digits.size())
            this->digits.push_back(0);
        
        this->digits[i] += carry;

        carry = this->digits[i] >= Natural::BASE;
        if (carry) this->digits[i] -= Natural::BASE;  
    }
    return *this;
}

Natural Natural::operator++(int) {
    Natural old = *this;
    operator++();
    return old;
}

Natural::operator bool() const
{
    return (digits.size() > 1) || (digits[0] != 0);
}

Natural subNDN(const Natural &lhs, const Natural &rhs, const Natural::Digit& digit){
    Natural res = lhs - (rhs * digit);
    return res;
}

Natural greatCommDiv(const Natural &lhs, const Natural &rhs){
    Natural left(lhs), right(rhs);

    while (left && right){
        if (left > right){
            left %= right;
        }
        else{
            right %= left;
        }
    }
    
    return left + right;
}

Natural leastCommMul(const Natural &lhs, const Natural &rhs){
    Natural GCF = greatCommDiv(lhs, rhs);
    return (lhs * rhs) / GCF;
}

Natural mod10k(const Natural &number, const size_t &k) {
    Natural res = number;

    //taking first k numbers from lower and cutting others
    res.digits.resize(k);

    return res;
}

Natural div10k(const Natural &number, const size_t &k) {
    Natural res = number;

    std::reverse(res.digits.begin(), res.digits.end());

    //taking last len(number) - k numbers and cutting fist k numbers
    res.digits.resize(number.digits.size() - k);

    std::reverse(res.digits.begin(), res.digits.end());

    return res;
}

Natural karatsuba_mul(const Natural &lhs, const Natural &rhs) {
    //recursion base if lhs or rhs < 10 -> digit * number
    if (lhs.digits.size() <= Natural::THRESHOLD || rhs.digits.size() <= Natural::THRESHOLD) {
        return lhs * rhs;
    }

    size_t len = std::max(lhs.digits.size(), rhs.digits.size());
    size_t k = len / 2;

    //parts if original lhs, rhs
    Natural lhs_l, lhs_r, rhs_l, rhs_r;

    //spliting lhs and rhs into to parts - left and right (low and high)
    lhs_r = div10k(lhs, k);
    lhs_l = mod10k(lhs, k);

    rhs_r = div10k(rhs, k);
    rhs_l = mod10k(rhs, k);

    //temporary tricky sum
    Natural t1 = lhs_r + lhs_l;
    Natural t2 = rhs_r + rhs_l;

    //counting 3 products instead of 4
    Natural p1 = karatsuba_mul(lhs_r, rhs_r);
    Natural p2 = karatsuba_mul(lhs_l, rhs_l);
    Natural p3 = karatsuba_mul(t1, t2);
    
    //couting result = p1*10^(2k) + (p3 - p2 - p1)*10^k + p2
    //doing that faster without copying
    p3 -= p2;
    p3 -= p1;
    p3 <<= k;
    p1 <<= 2*k;
    p1 += p3;
    p1 += p2;

    //difficulty O(n^log2(3))
    return p1;
}