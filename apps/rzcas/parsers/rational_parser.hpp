#ifndef CAS_RATIONAL_PARSER_HPP_
#define CAS_RATIONAL_PARSER_HPP_

#include "../parser.hpp"

class RationalParser : public Parser {
public:
    RationalParser(const char *str);
    std::string evaluate();
};

#endif
