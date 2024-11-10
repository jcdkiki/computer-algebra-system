#include "lexer.hpp"
#include <cctype>

bool is_identifier_char(char c) noexcept {
    return isalnum(c) || c == '_';
}

Token Lexer::atom(Token::Kind kind) noexcept { return Token(kind, m_beg++, 1); }

Token Lexer::next() {
    while (isspace(peek())) get();

    char c = peek();
    
    if (c == '\0') {
        return Token(Token::Kind::End, "<eof>", 5); 
    }
    if (isalpha(c) || c == '_') {
        return identifier();
    }
    if (isdigit(c)) {
        return number();
    }
    
    switch (c) {
        case '(': return atom(Token::Kind::LeftParen);
        case ')': return atom(Token::Kind::RightParen);
        case '+': return atom(Token::Kind::Plus);
        case '-': return atom(Token::Kind::Minus);
        case '*': return atom(Token::Kind::Asterisk);
        case '/': return atom(Token::Kind::Slash);
        case '%': return atom(Token::Kind::Percent);
        case ',': return atom(Token::Kind::Comma);
        case '^': return atom(Token::Kind::Caret);
        default:  return atom(Token::Kind::Unexpected);
    }
}

Token Lexer::number() noexcept
{
    const char* start = m_beg;
    get();
    while (isdigit(peek())) get();
    return Token(Token::Kind::Number, start, m_beg);
}

Token Lexer::identifier() noexcept {
    const char* start = m_beg;
    get();
    while (is_identifier_char(peek())) get();
    return Token(Token::Kind::Identifier, start, m_beg);
}
