#include "Stmt.hpp"

Stmt::Stmt(SourceSector sector) : sector(sector)
{
}

SourceSector Stmt::get_sector()
{
    return sector;
}
