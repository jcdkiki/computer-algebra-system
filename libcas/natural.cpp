#include "natural.hpp"
#include <algorithm>
#include <iostream>
#include <cctype>

Natural::Natural() : digits(1, 0) {}

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

Natural Natural::operator-(const Natural &number) const {
    Natural res(*this);
    if (number > res) {
        throw std::runtime_error("cannot sub from fewer number");
    }

    Natural::Digit carry = 0;
    for (size_t i = 0; i < number.digits.size() || carry; ++i) {
        res.digits[i] -= carry + ((i < number.digits.size()) ? number.digits[i]: 0);
        carry = res.digits[i] < 0;
        if (carry) res.digits[i] += Natural::BASE;
    }

    // strip insignificant zeros
    while (res.digits.size() > 1 && res.digits.back() == 0) {
        res.digits.pop_back();
    }

    return res;
}

Natural& Natural::operator-=(const Natural &number) {
    if (number > *this) {
        throw std::runtime_error("cannot sub from fewer number");
    }

    Natural::Digit carry = 0;
    for (size_t i = 0; i < this->digits.size() || carry; ++i) {
        this->digits[i] -= carry + ((i < number.digits.size()) ? number.digits[i]: 0);
        carry = this->digits[i] < 0;
        if (carry) this->digits[i] += Natural::BASE;
    }

    // strip insignificant zeros
    while (this->digits.size() > 1 && this->digits.back() == 0) {
        this->digits.pop_back();
    }

    return *this;
}

Natural& Natural::operator--() {
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

Natural::operator bool()
{
    return (digits.size() > 1) || (digits[0] != 0);
}
