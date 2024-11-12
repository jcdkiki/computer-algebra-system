#ifndef CAS_NATURAL_PARSER_HPP_
#define CAS_NATURAL_PARSER_HPP_

#include "../parser.hpp"

class NaturalParser : public Parser {
public:
    NaturalParser(const char *str);
    std::string evaluate();
};

#endif
