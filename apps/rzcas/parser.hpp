#ifndef CAS_COMMON_PARSER_HPP_
#define CAS_COMMON_PARSER_HPP_

#include <cctype>
#include <string>
#include <typeindex>
#include <unordered_map>
#include <vector>

#include "lexer.hpp"

class ParserException {
    int location_;
    std::string what_;
public:
    ParserException(int location_, std::string_view what_)
        : location_(location_), what_(what_)
    {}

    int location() const noexcept { return location_; }
    std::string_view what() const noexcept { return what_; }
};

class FunctionException {
    std::string what_;
public:
    FunctionException(std::string_view what_) : what_(what_) {}
    std::string_view what() const noexcept { return what_; }
};

class Parser {
protected:
    Lexer lexer;
    Token token;
    int location;

    typedef void (*FunctionPtr)(void *data, size_t n, void *out);
    std::unordered_map<std::string, std::unordered_map<std::type_index, FunctionPtr>> functions;
    
    inline ParserException error(std::string_view str)
    {
        return ParserException(location, str);
    }

    template<class ValueType>
    ValueType execute_function(std::string &name, std::vector<ValueType> &args);

    void eat();
    void expect(Token::Kind expected, const char *expected_str);
    void eat_expected(Token::Kind expected, const char *expected_str);

    template<class ValueType>
    ValueType evaluate_parenthesis();

    template<class ValueType>
    ValueType evaluate_value();

    template<class ValueType>
    ValueType evaluate_unary();

    template<class ValueType>
    ValueType evaluate_mul();

    template<class ValueType>
    ValueType evaluate_sum();

    template<class ValueType>
    ValueType evaluate_function();

    template<class ValueType>
    ValueType evaluate_whole_expression();

public:
    Parser(const char *str);

    virtual ~Parser() = default;

    virtual std::string evaluate() = 0;
};

template<class ValueType>
ValueType Parser::evaluate_function()
{
    expect(Token::Kind::Identifier, "identifier");
    std::string function_name(token.lexeme());
    eat();
    eat_expected(Token::Kind::LeftParen, "'('");

    std::vector<ValueType> arguments;

    if (token.is(Token::Kind::RightParen)) {
        eat();
        return execute_function(function_name, arguments);
    }

    while (true) {
        arguments.push_back(evaluate_sum<ValueType>());

        if (token.kind() == Token::Kind::RightParen) {
            eat();
            break;
        }
        if (token.kind() == Token::Kind::Comma) {
            eat();
            continue;
        }
        
        expect(Token::Kind::Nothing, "')' or ','");
    }

    return execute_function(function_name, arguments);
}

template<class ValueType>
ValueType Parser::execute_function(std::string &name, std::vector<ValueType> &args)
{
    const auto &function_by_name = functions.find(name);
    if (function_by_name == functions.end()) {
        throw error("cannot find function with name '" + name + "'");
    }

    const auto &function_by_type = function_by_name->second.find(std::type_index(typeid(ValueType)));
    if (function_by_type == function_by_name->second.end()) {
        throw error("cannot find overload of function '" + name + "' for required type");
    }

    try {
        ValueType res;
        function_by_type->second(args.data(), args.size(), &res);
        return res;
    }
    catch (FunctionException &e) {
        throw error("when calling function '" + name + "': " + e.what().data());
    }
}

template<class ValueType>
ValueType Parser::evaluate_parenthesis()
{
    eat_expected(Token::Kind::LeftParen, "'('");
    ValueType res = evaluate_sum<ValueType>();
    eat_expected(Token::Kind::RightParen, "')'");
    
    return res;
}

template<class ValueType>
ValueType Parser::evaluate_unary()
{
    switch (token.kind()) {
        case Token::Kind::LeftParen:    return evaluate_parenthesis<ValueType>();
        case Token::Kind::Identifier:   return evaluate_function<ValueType>();
        default:                        return evaluate_value<ValueType>();
    }
}

template<class ValueType>
ValueType Parser::evaluate_whole_expression()
{
    ValueType res = evaluate_sum<ValueType>();
    expect(Token::Kind::End, "end of input");
    return res;
}

template<class ValueType>
ValueType Parser::evaluate_sum()
{
    ValueType res = evaluate_mul<ValueType>();
    bool sign = false;

    while (true) {
        switch (token.kind()) {
            case Token::Kind::Plus:     sign = false; break;
            case Token::Kind::Minus:    sign = true; break;
            default:                    return res;
        }
        
        eat();
        ValueType tmp = evaluate_mul<ValueType>();
        
        if (sign) res -= tmp;
        else      res += tmp;
    }
}

template<class ValueType>
ValueType Parser::evaluate_mul()
{
    enum class Operation {
        Mul,
        Div,
        Mod
    };
    
    ValueType res = evaluate_unary<ValueType>();
    Operation operation = Operation::Mul;

    while (true) {
        switch (token.kind()) {
            case Token::Kind::Asterisk: operation = Operation::Mul; break;
            case Token::Kind::Slash:    operation = Operation::Div; break;
            case Token::Kind::Percent:  operation = Operation::Mod; break;
            default:                    return res;
        }

        eat();
        ValueType tmp = evaluate_unary<ValueType>();
        
        switch (operation) {
            case Operation::Mul: res *= tmp; break;
            case Operation::Div: res /= tmp; break;
            case Operation::Mod: res %= tmp; break;
        }
    }
}

#endif
