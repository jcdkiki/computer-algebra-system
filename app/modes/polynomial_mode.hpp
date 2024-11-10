#ifndef CAS_POLYNOMIAL_MODE_HPP_
#define CAS_POLYNOMIAL_MODE_HPP_

#include "../common_mode.hpp"

class PolynomialMode : public CommonMode {
    CasButton b_derivative;
    CasButton b_x;
    CasButton b_multiple_roots;
    CasButton b_power;
public:
    Parser *create_parser(const char *str);
    PolynomialMode();
};

#endif
