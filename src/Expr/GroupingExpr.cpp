#include "GroupingExpr.hpp"
#include "VisitorExpr.hpp"

GroupingExpr::GroupingExpr(ExprPtr p_pExpr, SourceSector position) : Expr(position),
                                                                      expr(std::move(p_pExpr))

{
}

void GroupingExpr::visit(VisitorExpr *visitor)
{
    visitor->visitGrouping(this);
}

Expr *GroupingExpr::get_expr()
{
    return expr.get();
}

void GroupingExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "Grouping:\n";

    expr->print_tree(os, indent + 1);
}

void GroupingExpr::print_source(std::ostream &os) const
{
    os << "(";
    expr->print_source(os);
    os << ")";
}
