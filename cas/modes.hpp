#ifndef CAS_MODES_HPP_
#define CAS_MODES_HPP_

#include "common_mode.hpp"
#include "common_parser.hpp"
#include "natural.hpp"

class NaturalMode : public CommonMode {
    CasButton b_gcd;
    CasButton b_lcm;

    CommonParser<Natural> parser;
public:
    NaturalMode();
};

class IntegerMode : public NaturalMode {
    CasButton b_abs;
public:
    IntegerMode();
};

class RationalMode : public CommonMode {
    CasButton b_reduce;
public:
    RationalMode();
};

class PolynomialMode : public CommonMode {
    CasButton b_derivative;
    CasButton b_x;
    CasButton b_multiple_roots;
    CasButton b_power;
public:
    PolynomialMode();
};

#endif
