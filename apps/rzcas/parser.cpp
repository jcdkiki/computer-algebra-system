#include "parser.hpp"

Parser::Parser(const char *str) : lexer(str), location(0), token(Token::Kind::End)
{
    eat();
}

void Parser::expect(Token::Kind expected, const char *expected_str)
{
    if (token.is_not(expected)) {
        throw error("unexpected token '" + std::string(token.lexeme()) + "', expected " + expected_str + "");
    }
}

void Parser::eat_expected(Token::Kind expected, const char *expected_str)
{
    expect(expected, expected_str);
    eat();
}

void Parser::eat()
{
    token = lexer.next();
    location++;

    if (token.is(Token::Kind::Unexpected)) {
        throw error("unexpected symbol '" + std::string(token.lexeme()) + "'");
    }
}
