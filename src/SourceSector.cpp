#include "SourceSector.hpp"

#include <ostream>
#include <cmath>

std::ostream &operator<<(std::ostream &out, const SourceSector &value)
{
    if (value.begin.get_line() == value.end.get_line())
    {
        out << value.begin.get_line() << ":" << value.begin.get_column();
        if (value.begin.get_column() != value.end.get_column())
        {
            out << "-" << value.end.get_column();
        }
    }
    else
    {
        out << value.begin.get_line() << ":" << value.begin.get_column() << " - " << value.end.get_line() << ":" << value.end.get_column();
    }

    return out;
}

SourceSector::SourceSector(SourcePosition begin, SourcePosition end) : begin(begin), end(end)
{
}

SourceSector SourceSector::merge(const SourceSector &other) const
{
    uint16_t line_begin = begin.get_line();
    uint16_t column_begin = begin.get_column();

    if (other.begin.get_line() < line_begin)
    {
        line_begin = other.begin.get_line();
        column_begin = other.begin.get_column();
    }
    if (begin.get_line() == other.begin.get_line())
    {
        column_begin = std::min(begin.get_column(), other.begin.get_column());
    }

    uint16_t line_end = end.get_line();
    uint16_t column_end = end.get_column();

    if (other.end.get_line() > line_end)
    {
        line_end = other.end.get_line();
        column_end = other.end.get_column();
    }
    if (end.get_line() == other.end.get_line())
    {
        column_end = std::max(end.get_column(), other.end.get_column());
    }

    return SourceSector(SourcePosition(line_begin, column_begin), SourcePosition(line_end, column_end));
}
