#pragma once

#include "Expr.hpp"

class VarExpr : public Expr
{

private:
    std::string name;
    
public:
    VarExpr(std::string name, SourceSector position);
    void visit(VisitorExpr *visitor);
    std::string get_name();

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os) const override;
};
