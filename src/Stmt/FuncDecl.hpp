#pragma once

#include "Stmt/Stmt.hpp"
#include "Datatypes/Datatype.hpp"
#include "BlockStmt.hpp"

#include <vector>

class FuncDecl : public Stmt
{
private:
    std::string name;
    DatatypePtr return_type;
    std::unique_ptr<BlockStmt> body;
    std::vector<std::pair<DatatypePtr, std::string>> args;

public:
    FuncDecl(std::string name, DatatypePtr return_type, std::unique_ptr<BlockStmt> body, SourceSector sector);
    void visit(VisitorStmt *visitor);
    BlockStmt *get_body();
    std::string get_name() const;
    Datatype *get_return_type() const;
    std::vector<std::pair<DatatypePtr, std::string>>::iterator begin();
    std::vector<std::pair<DatatypePtr, std::string>>::iterator end();
    unsigned int get_arity() const;
    void add_arg(std::string name, DatatypePtr datatype);

    virtual void print_tree(std::ostream &os, int indent = 0) const override;
	virtual void print_source(std::ostream &os, int indent = 0) const override;
};
