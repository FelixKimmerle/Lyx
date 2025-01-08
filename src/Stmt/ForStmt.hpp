#pragma once
#include "Stmt.hpp"
#include "../Expr/Expr.hpp"

class ForStmt : public Stmt
{
private:
	ExprPtr condition;
	StmtPtr body;
	StmtPtr initializer;
	ExprPtr increment;

public:
	ForStmt(ExprPtr condition, StmtPtr body, StmtPtr initializer, ExprPtr increment, SourceSector position);
	Expr *get_condition();
	Stmt *get_body();
	Stmt *get_initializer();
	Expr *get_increment();
	void visit(VisitorStmt *visitor);

	virtual void print_tree(std::ostream &os, int indent = 0) const override;
	virtual void print_source(std::ostream &os, int indent = 0) const override;
};
