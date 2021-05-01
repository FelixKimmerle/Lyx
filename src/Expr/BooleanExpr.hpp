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
};
