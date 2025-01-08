#include "indent.hpp"

void indent_str(std::ostream &os, int indent)
{
    // os << std::string(indent, ' ');

    for (int i = 0; i < indent; i++)
    {
        os << "  ";
    }
}