#pragma once

#include "Expr.hpp"

class UnaryExpr : public Expr
{
public:
    enum UnaryOperator
    {
        MINUS,
        BANG,
    };

private:
    ExprPtr expr;
    UnaryOperator unary_operator;

public:
    UnaryExpr(ExprPtr expr, UnaryOperator unary_operator, SourceSector position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    UnaryOperator get_unary_operator();

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
