#ifndef CAS_INTEGER_PARSER_HPP_
#define CAS_INTEGER_PARSER_HPP_

#include "../parser.hpp"

class IntegerParser : public Parser {
public:
    using Parser::Parser;
    std::string evaluate();
};

#endif
