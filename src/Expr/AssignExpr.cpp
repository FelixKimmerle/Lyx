#include "AssignExpr.hpp"
#include "VisitorExpr.hpp"

AssignExpr::AssignExpr(std::unique_ptr<VarExpr> var_expr, ExprPtr expr, SourceSector position) : Expr(position),
                                                                                                  var_expr(std::move(var_expr)),
                                                                                                  expr(std::move(expr))

{
}

void AssignExpr::visit(VisitorExpr *visitor)
{
    visitor->visitAssign(this);
}

Expr *AssignExpr::get_expr()
{
    return expr.get();
}

VarExpr *AssignExpr::get_var_expr()
{
    return var_expr.get();
}

void AssignExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "AssignExpr: \n";

    var_expr->print_tree(os, indent + 1);
    os << std::string(indent, ' ') << " = ";
    expr->print_tree(os, indent + 1);
}

void AssignExpr::print_source(std::ostream &os) const
{
    var_expr->print_source(os);
    os << " = ";
    expr->print_source(os);
}
