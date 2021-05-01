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
};
