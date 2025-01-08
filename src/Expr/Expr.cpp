#include "Expr.hpp"
#include <iostream>

Expr::Expr(SourceSector sector) : sector(sector)
{
}

Expr::~Expr()
{
}

SourceSector Expr::get_sector()
{
    return sector;
}

std::ostream &operator<<(std::ostream &os, const Expr &node)
{
     node.print_source(os);
     return os;
}
