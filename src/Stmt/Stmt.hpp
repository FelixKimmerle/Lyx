#pragma once

#include "SourceSector.hpp"
#include "../indent.hpp"

#include <memory>

class VisitorStmt;
class Stmt
{
protected:
    SourceSector sector;

public:
    Stmt(SourceSector sector);
    virtual ~Stmt();
    virtual void visit(VisitorStmt *visitor) = 0;
    virtual SourceSector get_sector();

    virtual void print_tree(std::ostream &os, int indent = 0) const = 0;
    virtual void print_source(std::ostream &os, int indent = 0) const = 0;

};

typedef std::unique_ptr<Stmt> StmtPtr;