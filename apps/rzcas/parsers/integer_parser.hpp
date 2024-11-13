#ifndef CAS_INTEGER_PARSER_HPP_
#define CAS_INTEGER_PARSER_HPP_

#include "../parser.hpp"

class IntegerParser : public Parser {
public:
    IntegerParser(const char *str);
    std::string evaluate();
};

#endif
