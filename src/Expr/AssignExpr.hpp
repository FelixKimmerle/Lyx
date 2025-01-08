#pragma once

#include "Expr.hpp"
#include "VarExpr.hpp"

class AssignExpr : public Expr
{
private:
    std::unique_ptr<VarExpr> var_expr;
    ExprPtr expr;

public:
    AssignExpr(std::unique_ptr<VarExpr> var_expr, ExprPtr expr, SourceSector position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    VarExpr *get_var_expr();

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
