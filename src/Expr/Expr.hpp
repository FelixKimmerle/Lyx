#pragma once
#include "SourceSector.hpp"
#include "../indent.hpp"

#include <memory>
#include <iostream>

class VisitorExpr;
class Expr
{
protected:
    SourceSector sector;

public:
    Expr(SourceSector sector);
    virtual ~Expr();
    virtual void visit(VisitorExpr *p_pVisitor) = 0;
    virtual SourceSector get_sector();
    friend std::ostream & operator<<(std::ostream &os, const Expr &node);
    virtual void print_tree(std::ostream &os, int indent = 0) const = 0;
    virtual void print_source(std::ostream &os) const = 0;
};

typedef std::unique_ptr<Expr> ExprPtr;