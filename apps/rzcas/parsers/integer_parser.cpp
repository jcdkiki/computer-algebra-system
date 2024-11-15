#include "integer_parser.hpp"
#include "rznumbers/integer.hpp"
#include "rznumbers/natural.hpp"

static void gcd_wrapper(Integer *data, size_t n, Integer *out)
{
    if (n != 2) {
        throw FunctionException("fucntion reqires 2 arguments");
    }

    *out = Integer(greatCommDiv(abs(data[0]), abs(data[1])));
}

static void lcm_wrapper(Integer *data, size_t n, Integer *out)
{
    if (n != 2) {
        throw FunctionException("fucntion reqires 2 arguments");
    }

    *out = Integer(leastCommMul(abs(data[0]), abs(data[1])));
}

static void abs_wrapper(Integer *data, size_t n, Integer *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = Integer(abs(data[0]));
}

IntegerParser::IntegerParser(const char *str) : Parser(str)
{
    functions["gcd"][std::type_index(typeid(Integer))] = (Parser::FunctionPtr)gcd_wrapper;
    functions["lcm"][std::type_index(typeid(Integer))] = (Parser::FunctionPtr)lcm_wrapper;
    functions["abs"][std::type_index(typeid(Integer))] = (Parser::FunctionPtr)abs_wrapper;
}

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
    
    Integer res = evaluate_unary<Integer>();
    res *= Integer(-1);
    return std::move(res);
}
