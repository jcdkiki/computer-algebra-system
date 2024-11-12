#ifndef CAS_POLYNOMIAL_PARSER_HPP_
#define CAS_POLYNOMIAL_PARSER_HPP_

#include "../parser.hpp"

class PolynomialParser : public Parser {
public:
    PolynomialParser(const char *str);
    std::string evaluate();
};

#endif
