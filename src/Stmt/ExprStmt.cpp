#include "Stmt/ExprStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
#include "ExprStmt.hpp"

ExprStmt::ExprStmt(ExprPtr p_pExpr, SourceSector position) : Stmt(position),
                                                             expr(std::move(p_pExpr))
{
}

void ExprStmt::visit(VisitorStmt *visitor)
{
    visitor->visitExprStmt(this);
}

Expr *ExprStmt::get_expr()
{
    return expr.get();
}

void ExprStmt::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "ExprStmt: \n";
    expr->print_tree(os, indent + 1);
}

void ExprStmt::print_source(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    expr->print_source(os);
    os << ";\n";
}
