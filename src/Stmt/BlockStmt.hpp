#pragma once

#include "Stmt/Stmt.hpp"
#include <vector>

class BlockStmt : public Stmt
{
private:
    std::vector<StmtPtr> stmts;
    bool constructed;

public:
    BlockStmt(SourceSector position, bool constructed = true);
    virtual void visit(VisitorStmt *visitor);
    std::vector<StmtPtr>::const_iterator begin()const;
    std::vector<StmtPtr>::const_iterator end()const;
    void add(StmtPtr stmt);

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
    virtual void print_source(std::ostream &os, int indent = 0) const override;
};
