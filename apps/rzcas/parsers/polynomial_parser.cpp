#include "polynomial_parser.hpp"
#include "rznumbers/polynomial.hpp"
#include "rznumbers/rational.hpp"

static void derivative(Polynomial *data, size_t n, Polynomial *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = data->derivative();
}

PolynomialParser::PolynomialParser(const char *str) : Parser(str)
{
    functions["derivative"][std::type_index(typeid(Polynomial))] = (Parser::FunctionPtr)derivative;
}

std::string PolynomialParser::evaluate()
{
    return evaluate_whole_expression<Polynomial>().asString();
}

template<>
Rational Parser::evaluate_mul<Rational>();

template<>
Polynomial Parser::evaluate_value<Polynomial>()
{
    Rational coeff = Rational(1);
    
    if (token.is_not(Token::Kind::X)) {
        coeff = evaluate_unary<Rational>();
    }
    
    if (token.is_not(Token::Kind::X)) {
        return Polynomial(coeff, 0);
    }
    eat();

    if (token.is_not(Token::Kind::Caret)) {
        return Polynomial(coeff, 1);
    }
    eat();

    int power = evaluate_unary<int>();
    if (power < 0) {
        throw error("power of monome is less than zero");
    }

    return Polynomial(coeff, power);
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
