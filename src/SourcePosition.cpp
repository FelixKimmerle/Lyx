#include "SourcePosition.hpp"

#include <ostream>

std::ostream &operator<<(std::ostream &out, const SourcePosition &value)
{
    out << ":" << value.line << ":" << value.column;
    return out;
}

SourcePosition::SourcePosition(unsigned int line, unsigned int column) : line(line), column(column)
{
}

uint16_t SourcePosition::get_line() const
{
    return line;
}

uint16_t SourcePosition::get_column() const
{
    return column;
}

void SourcePosition::new_line()
{
    line++;
    column = 0;
}
void SourcePosition::new_column()
{
    column++;
}