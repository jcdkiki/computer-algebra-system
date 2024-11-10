#include "integer_parser.hpp"
#include "rznumbers/integer.hpp"

std::string IntegerParser::evaluate()
{
    return evaluate_whole_expression<Integer>().asString();
}

template<>
Integer Parser::evaluate_value<Integer>()
{
    if (token.is(Token::Kind::Number)) {
        Integer res(token.lexeme_cstr());
        eat();
        return std::move(res);
    }
    
    eat_expected(Token::Kind::Minus, "number or '-'");
    return evaluate_unary<Integer>() * Integer("-1");
}
