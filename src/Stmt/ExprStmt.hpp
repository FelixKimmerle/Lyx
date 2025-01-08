#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class ExprStmt : public Stmt
{
private:
    ExprPtr expr;

public:
    ExprStmt(ExprPtr expr, SourceSector position);
    void visit(VisitorStmt *visitor);
    Expr *get_expr();

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os, int indent = 0) const override;
};
