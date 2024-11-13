#ifndef CAS_LEXER_HPP_
#define CAS_LEXER_HPP_

#include <string>

class LexerException {
    std::string m_what;
public:
    LexerException(std::string_view m_what) : m_what(m_what) {}
    std::string_view what() const noexcept { return m_what; }
};

class Token {
public:
    enum class Kind {
        Nothing,
        Number,
        Identifier,
        LeftParen,
        RightParen,
        Plus,
        Minus,
        Asterisk,
        Slash,
        Percent,
        Comma,
        Caret,
        X,
        D,
        DX,
        End,
        Unexpected,
    };

    Token(Kind kind) noexcept : m_kind{kind} {}

    Token(Kind kind, const char* beg, std::size_t len) noexcept
        : m_kind{kind}, m_lexeme(beg, len)
    {}

    Token(Kind kind, const char* beg, const char* end) noexcept
        : m_kind{kind}, m_lexeme(beg, std::distance(beg, end))
    {}

    Kind kind() const noexcept { return m_kind; }

    void kind(Kind kind) noexcept { m_kind = kind; }

    bool is(Kind kind) const noexcept { return m_kind == kind; }

    bool is_not(Kind kind) const noexcept { return m_kind != kind; }

    bool is_one_of(Kind k1, Kind k2) const noexcept { return is(k1) || is(k2); }

    template <typename... Ts>
    bool is_one_of(Kind k1, Kind k2, Ts... ks) const noexcept
    {
        return is(k1) || is_one_of(k2, ks...);
    }

    std::string_view lexeme() const noexcept { return m_lexeme; }
    const char *lexeme_cstr() const noexcept { return m_lexeme.data(); }

    void lexeme(std::string_view lexeme) noexcept {
        m_lexeme = std::move(lexeme);
    }

    private:
        Kind                m_kind{};
        std::string_view    m_lexeme{};
};

class Lexer {
public:
    Lexer(const char* beg) noexcept : m_beg{beg} {}

    Token next();

protected:
    Token identifier() noexcept;
    Token atom(Token::Kind) noexcept;
    Token number() noexcept;
    
    char peek() const noexcept { return *m_beg; }
    char get() noexcept { return *m_beg++; }

    const char* m_beg = nullptr;
};

#endif
