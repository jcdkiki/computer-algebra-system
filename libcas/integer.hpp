#ifndef CAS_NUMBERS_INTEGER_HPP_
#define CAS_NUMBERS_INTEGER_HPP_

#include <vector>
#include <string>
#include <ostream>
#include <istream>

class Integer {
    using Digit = unsigned char;
    std::vector<Digit> digits;
    bool sign;
public:
    Integer();
    explicit Integer(const char *str);
    std::string asString();

    bool isZero();

    friend std::ostream& operator<<(std::ostream& os, const Integer& number);
    friend std::istream& operator>>(std::istream& is, Integer& number);
};

std::ostream& operator<<(std::ostream& os, const Integer& number);
std::istream& operator>>(std::istream& is, Integer& number);

#endif
