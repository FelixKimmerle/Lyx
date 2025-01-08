#pragma once

#include "Stmt/Stmt.hpp"
#include "Expr/Expr.hpp"
#include "Datatypes/Datatype.hpp"
#include <string>

class VarStmt : public Stmt
{
private:
    ExprPtr initializer;
    DatatypePtr type;
    std::string name;

public:
    VarStmt(std::string name, DatatypePtr type, ExprPtr initializer, SourceSector position);
    virtual void visit(VisitorStmt *visitor);
    Expr *get_initializer()const;
    Datatype *get_type()const;
    std::string get_name()const;

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os, int indent = 0) const override;
};
