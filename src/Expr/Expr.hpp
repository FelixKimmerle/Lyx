#pragma once
#include "SourceSector.hpp"

#include <memory>

class VisitorExpr;
class Expr
{
protected:
    SourceSector sector;

public:
    Expr(SourceSector sector);
    virtual void visit(VisitorExpr *p_pVisitor) = 0;
    virtual SourceSector get_sector();
};

typedef std::unique_ptr<Expr> ExprPtr;