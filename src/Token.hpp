#pragma once

#include "SourceSector.hpp"

#include <string>

class Token
{
public:
    enum class TokenType
    {
        // Single-character tokens.
        TOKEN_LEFT_PAREN,
        TOKEN_RIGHT_PAREN,
        TOKEN_LEFT_BRACE,
        TOKEN_RIGHT_BRACE,
        TOKEN_COMMA,
        TOKEN_DOT,
        TOKEN_MINUS,
        TOKEN_PLUS,
        TOKEN_SEMICOLON,
        TOKEN_SLASH,
        TOKEN_STAR,

        // One or two character tokens.
        TOKEN_BANG,
        TOKEN_BANG_EQUAL,
        TOKEN_EQUAL,
        TOKEN_EQUAL_EQUAL,
        TOKEN_GREATER,
        TOKEN_GREATER_EQUAL,
        TOKEN_LESS,
        TOKEN_LESS_EQUAL,

        // Literals.
        TOKEN_IDENTIFIER,
        TOKEN_STRING,
        TOKEN_NUMBER_BYTE,
        TOKEN_NUMBER_SHORT,
        TOKEN_NUMBER_INT,
        TOKEN_NUMBER_FLOAT,
        TOKEN_NUMBER_DOUBLE,
        TOKEN_NUMBER_LONG,

        // Keywords.
        TOKEN_AND,
        TOKEN_CLASS,
        TOKEN_ELSE,
        TOKEN_FALSE,
        TOKEN_FOR,
        TOKEN_FUN,
        TOKEN_IF,
        TOKEN_NIL,
        TOKEN_OR,
        TOKEN_PRINT,
        TOKEN_RETURN,
        TOKEN_SUPER,
        TOKEN_THIS,
        TOKEN_TRUE,
        TOKEN_VAR,
        TOKEN_WHILE,
        TOKEN_BREAK,
        TOKEN_CONTINUE,

        // Datatypes
        TOKEN_INT64,
        TOKEN_UINT64,
        TOKEN_FLOAT,
        TOKEN_BOOL,

        TOKEN_ERROR,
        TOKEN_EOF
    };

private:
    TokenType type;
    std::string lexeme;
    SourceSector sector;
    friend std::ostream &operator<<(std::ostream &out, const Token &value);

public:
    Token(TokenType type = TokenType::TOKEN_ERROR, const std::string &lexeme = "", SourceSector sector = SourceSector());
    TokenType get_type()const;
    const std::string &get_lexeme()const;
    const SourceSector &get_sector()const;
};
