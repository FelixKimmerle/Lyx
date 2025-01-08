#include "Stmt/PrintStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
#include "PrintStmt.hpp"

PrintStmt::PrintStmt(ExprPtr expr, SourceSector position) : Stmt(position),
                                                            expr(std::move(expr))

{
}

void PrintStmt::visit(VisitorStmt *visitor)
{
    visitor->visitPrint(this);
}

Expr *PrintStmt::get_expr()
{
    return expr.get();
}
void PrintStmt::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "PrintStmt: \n";
    expr->print_tree(os, indent + 1);
}

void PrintStmt::print_source(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "print ";
    expr->print_source(os);
    os << ";";
}
