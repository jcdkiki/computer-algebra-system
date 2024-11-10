#ifndef CAS_NATURAL_MODE_HPP_
#define CAS_NATURAL_MODE_HPP_

#include "../common_mode.hpp"

class NaturalMode : public CommonMode {
    CasButton b_gcd;
    CasButton b_lcm;
public:
    Parser *create_parser(const char *str);
    NaturalMode();
};

#endif
