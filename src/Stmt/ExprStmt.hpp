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
};
