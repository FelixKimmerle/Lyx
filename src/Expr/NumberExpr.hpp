#pragma once
#include <string>
#include "Expr.hpp"

template <class T>
class NumberExpr : public Expr
{
private:
    T number;
public:
    NumberExpr(T number, SourceSector position);
    void visit(VisitorExpr *visitor);
    T get_number();
};
