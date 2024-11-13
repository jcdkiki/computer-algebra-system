#include "natural_parser.hpp"
#include "rznumbers/natural.hpp"

static void gcd_wrapper(Natural *data, size_t n, Natural *out)
{
    if (n != 2) {
        throw FunctionException("fucntion reqires at least 2 arguments");
    }

    *out = greatCommDiv(data[0], data[1]);
}

static void lcm_wrapper(Natural *data, size_t n, Natural *out)
{
    if (n != 2) {
        throw FunctionException("fucntion reqires 2 arguments");
    }

    *out = leastCommMul(data[0], data[1]);
}

NaturalParser::NaturalParser(const char *str) : Parser(str)
{
    functions["gcd"][std::type_index(typeid(Natural))] = (Parser::FunctionPtr)gcd_wrapper;
    functions["lcm"][std::type_index(typeid(Natural))] = (Parser::FunctionPtr)lcm_wrapper;
}

std::string NaturalParser::evaluate()
{
    return evaluate_whole_expression<Natural>().asString();
}

template<>
Natural Parser::evaluate_value<Natural>()
{
    expect(Token::Kind::Number, "number");
    Natural res(token.lexeme_cstr());
    eat();
    return std::move(res);
}
