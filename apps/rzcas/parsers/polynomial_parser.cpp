#include "polynomial_parser.hpp"
#include "rznumbers/polynomial.hpp"
#include "rznumbers/rational.hpp"

static void nmr(Polynomial *data, size_t n, Polynomial *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = data->nmr();
}

static void factorize(Polynomial *data, size_t n, Polynomial *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = data->factorize();
}

static void gcd_wrapper(Polynomial *data, size_t n, Polynomial *out)
{
    if (n != 2) {
        throw FunctionException("function requires 2 arguments");
    }

    *out = gcd(data[0], data[1]);
}

PolynomialParser::PolynomialParser(const char *str) : Parser(str)
{
    functions["fac"][std::type_index(typeid(Polynomial))] = (Parser::FunctionPtr)factorize;
    functions["nmr"][std::type_index(typeid(Polynomial))] = (Parser::FunctionPtr)nmr;
    functions["gcd"][std::type_index(typeid(Polynomial))] = (Parser::FunctionPtr)gcd_wrapper;
}

std::string PolynomialParser::evaluate()
{
    return std::move(evaluate_whole_expression<Polynomial>().asString());
}

template<>
Rational Parser::evaluate_mul<Rational>();

template<>
Polynomial Parser::evaluate_value<Polynomial>()
{
    if (token.is(Token::Kind::Minus)) {                 // unary "-"
        eat();                                          // dirty but ok for now...
        return std::move(evaluate_unary<Polynomial>()); // want to rewrite all this crap later......
    }

    if (token.is(Token::Kind::D)) {             // hardcoded pretty badly
        eat();
        eat_expected(Token::Kind::Slash, "d/dx(...)");
        eat_expected(Token::Kind::DX, "d/dx(...)");
        return std::move(evaluate_parenthesis<Polynomial>().derivative());
    }

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
