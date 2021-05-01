#include "VarExpr.hpp"
#include "VisitorExpr.hpp"
VarExpr::VarExpr(std::string name, SourceSector position) : Expr(position),
                                                             name(name)
{
}

void VarExpr::visit(VisitorExpr *visitor)
{
    visitor->visitVar(this);
}

std::string VarExpr::get_name()
{
    return name;
}
