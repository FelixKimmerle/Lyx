#include "BinaryExpr.hpp"
#include "VisitorExpr.hpp"
#include <iostream>
#include <cassert>
BinaryExpr::BinaryExpr(ExprPtr left, ExprPtr right, BinaryExpr::BinaryOperator binary_operator, SourceSector position) : Expr(position),
                                                                                                                         left(std::move(left)),
                                                                                                                         right(std::move(right)),
                                                                                                                         binary_operator(binary_operator)

{
}

void BinaryExpr::visit(VisitorExpr *visitor)
{
    visitor->visitBinary(this);
}

Expr *BinaryExpr::get_left()
{
    return left.get();
}
Expr *BinaryExpr::get_right()
{
    return right.get();
}
BinaryExpr::BinaryOperator BinaryExpr::get_binary_operator()
{
    return binary_operator;
}

std::string binop_to_string(BinaryExpr::BinaryOperator binop)
{
    switch (binop)
    {
    case BinaryExpr::BinaryOperator::ADD:
        return "+";
    case BinaryExpr::BinaryOperator::SUB:
        return "-";
    case BinaryExpr::BinaryOperator::MUL:
        return "*";
    case BinaryExpr::BinaryOperator::DIV:
        return "/";
    case BinaryExpr::BinaryOperator::AND:
        return "and";
    case BinaryExpr::BinaryOperator::OR:
        return "os";
    case BinaryExpr::BinaryOperator::EQUAL:
        return "==";
    case BinaryExpr::BinaryOperator::LESS:
        return "<";
    case BinaryExpr::BinaryOperator::LESS_EQUAL:
        return "<=";
    case BinaryExpr::BinaryOperator::GREATER:
        return ">";
    case BinaryExpr::BinaryOperator::GREATER_EQUAL:
        return ">=";
    }
    assert(false);
    return "ERROR";
}

void BinaryExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "BinaryExpr (" << binop_to_string(binary_operator) << ")\n";

    left->print_tree(os, indent + 1);
    right->print_tree(os, indent + 1);
}

void BinaryExpr::print_source(std::ostream &os) const
{
    left->print_source(os);
    os << " " << binop_to_string(binary_operator) << " ";
    right->print_source(os);
}
