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

void VarExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "VarExpr (" << name << ")\n";
}

void VarExpr::print_source(std::ostream &os) const
{
    os << name;
}
