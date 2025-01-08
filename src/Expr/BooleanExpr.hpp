#pragma once
#include <string>
#include "Expr.hpp"

class BooleanExpr : public Expr
{
private:
    bool boolean;

public:
    BooleanExpr(bool boolean, SourceSector position);
    void visit(VisitorExpr *visitor);
    bool get_boolean();
    virtual void print_tree(std::ostream &os,int indent = 0) const override;   
    virtual void print_source(std::ostream &os) const override;
};
