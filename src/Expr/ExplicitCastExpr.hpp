#pragma once

#include "Expr.hpp"
#include "Datatypes/Datatype.hpp"

class ExplicitCastExpr : public Expr
{
private:
    ExprPtr expr;
    DatatypePtr type;

public:
    ExplicitCastExpr(ExprPtr expr, DatatypePtr type, SourceSector position);
    void visit(VisitorExpr *visitor);
    Expr *get_expr();
    Datatype *get_type();
};
