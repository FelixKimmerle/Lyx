#include "ReturnStmt.hpp"
#include "VisitorStmt.hpp"
ReturnStmt::ReturnStmt(ExprPtr expr, SourceSector position) : Stmt(position),
                                                               expr(std::move(expr))

{
}

Expr *ReturnStmt::get_expr()
{
    return expr.get();
}


void ReturnStmt::visit(VisitorStmt *visitor)
{
    visitor->visitReturnStmt(this);
}

void ReturnStmt::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "ReturnStmt: \n";
    expr->print_tree(os, indent + 1); 
}

void ReturnStmt::print_source(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "return ";
    expr->print_source(os);
    os << ";";
}