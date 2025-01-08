#include "UnaryExpr.hpp"
#include "VisitorExpr.hpp"
UnaryExpr::UnaryExpr(ExprPtr expr, UnaryOperator unary_operator, SourceSector position) : Expr(position),
                                                                                               expr(std::move(expr)),
                                                                                               unary_operator(unary_operator)

{
}

void UnaryExpr::visit(VisitorExpr *visitor)
{
    visitor->visitUnary(this);
}

Expr *UnaryExpr::get_expr()
{
    return expr.get();
}

UnaryExpr::UnaryOperator UnaryExpr::get_unary_operator()
{
    return unary_operator;
}

std::string binop_to_string(UnaryExpr::UnaryOperator binop)
{
    switch (binop)
    {
    case UnaryExpr::UnaryOperator::MINUS:
        return "-";
    case UnaryExpr::UnaryOperator::BANG:
        return "!";
    
    }
    return "ERROR";
}

void UnaryExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "BinaryExpr (" << binop_to_string(unary_operator) << ")\n";
    expr->print_tree(os, indent + 1);

    
}

void UnaryExpr::print_source(std::ostream &os) const
{
    os << binop_to_string(unary_operator);
    expr->print_source(os);
}
