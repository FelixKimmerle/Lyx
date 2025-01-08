#pragma once

#include "Stmt.hpp"
#include "Expr/Expr.hpp"

class IfStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr then_body;
	StmtPtr else_body;

public:
	IfStmt(ExprPtr condition, StmtPtr then_body, StmtPtr else_body, SourceSector position);
	void visit(VisitorStmt *visitor);
	Expr *get_condition();
	Stmt *get_then();
	Stmt *get_else();

	virtual void print_tree(std::ostream &os, int indent = 0) const override;
	virtual void print_source(std::ostream &os, int indent = 0) const override;
};
