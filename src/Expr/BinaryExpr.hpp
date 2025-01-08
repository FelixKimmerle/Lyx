#pragma once

#include "Expr.hpp"

class BinaryExpr : public Expr
{
public:
    enum BinaryOperator
    {
        ADD,
        SUB,
        MUL,
        DIV,
        AND,
        OR,
        EQUAL,
        LESS,
        LESS_EQUAL,
        GREATER,
        GREATER_EQUAL,
    };

private:
    ExprPtr left;
    ExprPtr right;
    BinaryOperator binary_operator;

public:
    BinaryExpr(ExprPtr left, ExprPtr right, BinaryExpr::BinaryOperator binary_operator, SourceSector position);
    void visit(VisitorExpr *visitor);
    Expr *get_left();
    Expr *get_right();
    BinaryOperator get_binary_operator();
    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
