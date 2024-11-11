#include "polynomial_parser.hpp"
#include "rznumbers/polynomial.hpp"

typedef Polynomial<int, 0, 1> ShitPolynomial;

static void derivative(ShitPolynomial *data, size_t n, ShitPolynomial *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = data->derivative();
}

PolynomialParser::PolynomialParser(const char *str) : Parser(str)
{
    functions["derivative"][std::type_index(typeid(ShitPolynomial))] = (Parser::FunctionPtr)derivative;
}

std::string PolynomialParser::evaluate()
{
    return evaluate_whole_expression<ShitPolynomial>().asString();
}

template<>
ShitPolynomial Parser::evaluate_value<ShitPolynomial>()
{
    int coeff = 1;
    
    if (token.is_not(Token::Kind::X)) {
        coeff = evaluate_sum<int>();
    }
    
    if (token.is_not(Token::Kind::X)) {
        return ShitPolynomial(coeff, 0);
    }
    eat();

    if (token.is_not(Token::Kind::Caret)) {
        return ShitPolynomial(coeff, 1);
    }
    eat();

    int power = evaluate_unary<int>();
    if (power < 0) {
        throw error("power of monome is less than zero");
    }

    return ShitPolynomial(coeff, power);
}

template<>
int Parser::evaluate_value<int>()
{
    if (token.is(Token::Kind::Number)) {
        int res = atoi(token.lexeme_cstr());
        eat();
        return res;
    }
    
    eat_expected(Token::Kind::Minus, "number or '-'");
    return -evaluate_unary<int>();
}

/* Это временно */

template<>
ShitPolynomial Parser::evaluate_mul()
{
    return evaluate_unary<ShitPolynomial>();
}
