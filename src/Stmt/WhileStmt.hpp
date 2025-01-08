#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class WhileStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr body;

public:
	WhileStmt(ExprPtr condition, StmtPtr body, SourceSector position);
	void visit(VisitorStmt *visitor);
	Expr *get_condition();
	Stmt *get_body();

	virtual void print_tree(std::ostream &os, int indent = 0) const override;
	virtual void print_source(std::ostream &os, int indent = 0) const override;
};
