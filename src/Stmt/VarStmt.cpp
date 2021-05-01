#include "VarStmt.hpp"
#include "Stmt/VisitorStmt.hpp"
VarStmt::VarStmt(std::string name, DatatypePtr type, ExprPtr initializer, SourceSector sector) : Stmt(sector),
                                                                                                    initializer(std::move(initializer)),
                                                                                                    type(std::move(type)),
                                                                                                    name(name)

{
}

void VarStmt::visit(VisitorStmt *visitor)
{
    visitor->visitVar(this);
}

Expr *VarStmt::get_initializer()const
{
    return initializer.get();
}

Datatype *VarStmt::get_type()const
{
    return type.get();
}

std::string VarStmt::get_name()const
{
    return name;
}