#ifndef CAS_POLYNOMIAL_MODE_HPP_
#define CAS_POLYNOMIAL_MODE_HPP_

#include "../common_mode.hpp"

class PolynomialMode : public CommonMode {
    CasButton b_derivative;
    CasButton b_x;
    CasButton b_nmr;
    CasButton b_power;
    CasButton b_factorize;
public:
    Parser *create_parser(const char *str);
    PolynomialMode();
};

#endif
