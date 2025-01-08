
#include "BooleanExpr.hpp"
#include "VisitorExpr.hpp"

BooleanExpr::BooleanExpr(bool p_Boolean, SourceSector position) : Expr(position),
                                                                  boolean(p_Boolean)
{
}

void BooleanExpr::visit(VisitorExpr *visitor)
{
    visitor->visitBoolean(this);
}

bool BooleanExpr::get_boolean()
{
    return boolean;
}

void BooleanExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "Boolean: " << std::boolalpha << boolean << "\n";
}

void BooleanExpr::print_source(std::ostream &os) const
{
    os << std::boolalpha << boolean;
}
