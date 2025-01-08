#pragma once
#include "Expr.hpp"

class GroupingExpr : public Expr
{
private:
    ExprPtr expr;

public:
    GroupingExpr(ExprPtr expr, SourceSector position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
