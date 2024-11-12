#ifndef CAS_INTEGER_MODE_HPP_
#define CAS_INTEGER_MODE_HPP_

#include "natural_mode.hpp"

class IntegerMode : public NaturalMode {
    CasButton b_abs;
public:
    Parser *create_parser(const char *str);
    IntegerMode();
};

#endif
