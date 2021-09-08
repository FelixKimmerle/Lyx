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
