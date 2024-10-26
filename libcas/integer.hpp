#ifndef CAS_NUMBERS_INTEGER_HPP_
#define CAS_NUMBERS_INTEGER_HPP_

#include <vector>

class Integer {
    using Digit = unsigned char;
    std::vector<Digit> digits;
    bool sign;
};

#endif
