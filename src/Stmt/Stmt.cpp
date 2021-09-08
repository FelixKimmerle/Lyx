#include "Stmt.hpp"

Stmt::Stmt(SourceSector sector) : sector(sector)
{
}

Stmt::~Stmt()
{
}

SourceSector Stmt::get_sector()
{
    return sector;
}
