#ifndef CAS_RATIONAL_MODE_HPP_
#define CAS_RATIONAL_MODE_HPP_

#include "../common_mode.hpp"

class RationalMode : public CommonMode {
    CasButton b_inverse;
public:
    Parser *create_parser(const char *str);
    RationalMode();
};

#endif
