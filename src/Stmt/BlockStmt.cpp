#include "Stmt/BlockStmt.hpp"
#include "Stmt/VisitorStmt.hpp"

#include <iostream>
#include "BlockStmt.hpp"

BlockStmt::BlockStmt(SourceSector position, bool constructed) : Stmt(position), constructed(constructed)
{
}

void BlockStmt::visit(VisitorStmt *visitor)
{
    visitor->visitBlock(this);
}

std::vector<StmtPtr>::const_iterator BlockStmt::begin() const
{
    return stmts.cbegin();
}
std::vector<StmtPtr>::const_iterator BlockStmt::end() const
{
    return stmts.cend();
}

void BlockStmt::add(StmtPtr stmt)
{
    sector = sector.merge(stmt.get()->get_sector());
    stmts.push_back(std::move(stmt));
}

void BlockStmt::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "BlockStmt: (constructed: " << std::boolalpha << constructed << ")\n";
    for (const auto &stmt : stmts)
    {
        stmt->print_tree(os, indent + 1);
    }
}

void BlockStmt::print_source(std::ostream &os, int indent) const
{
    if (!constructed)
    {
        indent_str(os, std::max(0, indent - 1));
        os << "{\n";
    }
    for (const auto &stmt : stmts)
    {
        stmt->print_source(os, indent + (constructed ? 0 : 1));
        os << "\n";
    }
    if (!constructed)
    {
        indent_str(os, std::max(0, indent - 1));
        os << "}";
    }
}
