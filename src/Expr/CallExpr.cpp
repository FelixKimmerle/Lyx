#include "CallExpr.hpp"
#include "VisitorExpr.hpp"

CallExpr::CallExpr(ExprPtr callee, SourceSector position) : Expr(position),
                                                            callee(std::move(callee))
{
}

void CallExpr::visit(VisitorExpr *visitor)
{
    visitor->visitCall(this);
}

std::vector<ExprPtr>::iterator CallExpr::begin()
{
    return params.begin();
}
std::vector<ExprPtr>::iterator CallExpr::end()
{
    return params.end();
}

Expr *CallExpr::get_callee()
{
    return callee.get();
}

void CallExpr::add_param(ExprPtr param)
{
    params.push_back(std::move(param));
}

void CallExpr::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "CallExpr: \n";
    callee->print_tree(os, indent + 1);
    os << "\nArgs: \n";
    for(const auto & arg : params)
    {
        arg->print_tree(os, indent + 1);
        os << "\n";
    }
}

void CallExpr::print_source(std::ostream &os) const
{
    callee->print_source(os);
    os << "(";
    bool first = true;
    for(const auto & arg : params)
    {
        if(first)
        {
            first = false;
        }
        else
        {
            os << ",";
        }
        arg->print_source(os);
    }
    os << ")";
}