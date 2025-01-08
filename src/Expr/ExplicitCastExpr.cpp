#include "ExplicitCastExpr.hpp"
#include "VisitorExpr.hpp"
ExplicitCastExpr::ExplicitCastExpr(ExprPtr p_pExpr, DatatypePtr p_Type, SourceSector position) : Expr(position),
                                                                                                  expr(std::move(p_pExpr)),
                                                                                                  type(std::move(p_Type))

{
}

void ExplicitCastExpr::visit(VisitorExpr *visitor)
{
    visitor->visitExplicitCast(this);
}
Expr *ExplicitCastExpr::get_expr()
{
    return expr.get();
}
Datatype *ExplicitCastExpr::get_type()
{
    return type.get();
}

void ExplicitCastExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "cast (" << "TODO!!!" << ")\n";

    expr->print_tree(os, indent + 1);
}

void ExplicitCastExpr::print_source(std::ostream &os) const
{
    os << "TODO!!! datatype(";
    expr->print_source(os);
    os << ")";
}
