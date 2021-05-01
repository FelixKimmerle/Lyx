#include "Expr.hpp"

Expr::Expr(SourceSector sector) : sector(sector)
{
}

SourceSector Expr::get_sector()
{
    return sector;
}
