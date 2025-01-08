#include "Stmt.hpp"
#include <iostream>


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


