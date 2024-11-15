#include "rational_parser.hpp"
#include "rznumbers/rational.hpp"

static void inverse(Rational *data, size_t n, Rational *out)
{
    if (n != 1) {
        throw FunctionException("fucntion reqires 1 argument");
    }

    *out = Rational("1") / data[0];
}

RationalParser::RationalParser(const char *str) : Parser(str)
{
    functions["inv"][std::type_index(typeid(Rational))] = (Parser::FunctionPtr)inverse;
}

std::string RationalParser::evaluate()
{
    return std::move(evaluate_whole_expression<Rational>().asString());
}

template<>
Rational Parser::evaluate_value<Rational>()
{
    return Rational(evaluate_value<Integer>());
}


/* Эта специализация нужна, потому что для рациональных не определен %= */

template<>
Rational Parser::evaluate_mul()
{
    enum class Operation {
        Mul, Div
    };
    
    Rational res = evaluate_unary<Rational>();
    Operation operation = Operation::Mul;

    while (true) {
        switch (token.kind()) {
            case Token::Kind::Asterisk: operation = Operation::Mul; break;
            case Token::Kind::Slash:    operation = Operation::Div; break;
            default:                    return res;
        }

        eat();
        Rational tmp = evaluate_unary<Rational>();
        
        switch (operation) {
            case Operation::Mul: res *= tmp; break;
            case Operation::Div: res /= tmp; break;
        }
    }
}
