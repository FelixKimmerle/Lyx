
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
