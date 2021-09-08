#pragma once

#include "SourceSector.hpp"

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
};

typedef std::unique_ptr<Stmt> StmtPtr;