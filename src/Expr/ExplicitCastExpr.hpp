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
    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
