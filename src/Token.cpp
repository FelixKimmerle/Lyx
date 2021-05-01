#include "Token.hpp"

#include <ostream>
#include <iomanip>

std::ostream &operator<<(std::ostream &out, const Token &value)
{
    out << value.sector << " " << std::setfill(' ') << std::setw(2) << (int)value.type << " \'" << value.lexeme << "\'";
    return out;
}

Token::Token(TokenType type, const std::string &lexeme, SourceSector sector) : type(type), lexeme(lexeme), sector(sector)
{
}

Token::TokenType Token::get_type() const
{
    return type;
}

const std::string &Token::get_lexeme() const
{
    return lexeme;
}

const SourceSector &Token::get_sector() const
{
    return sector;
}