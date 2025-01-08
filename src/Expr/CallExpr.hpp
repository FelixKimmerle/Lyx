#pragma once
#include "Expr.hpp"
#include <vector>

class CallExpr : public Expr
{
private:
    ExprPtr callee;
    std::vector<ExprPtr> params;

public:
    CallExpr(ExprPtr callee, SourceSector position);
    void visit(VisitorExpr *p_pVisitor);
    Expr *get_callee();
    void add_param(ExprPtr param);
    std::vector<ExprPtr>::iterator begin();
    std::vector<ExprPtr>::iterator end();

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
