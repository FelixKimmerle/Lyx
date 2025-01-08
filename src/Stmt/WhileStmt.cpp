#include "WhileStmt.hpp"
#include "VisitorStmt.hpp"

WhileStmt::WhileStmt(ExprPtr condition, StmtPtr body, SourceSector position) : Stmt(position),
																				condition(std::move(condition)),
																				body(std::move(body))

{
}

Expr *WhileStmt::get_condition()
{
	return condition.get();
}

Stmt *WhileStmt::get_body()
{
	return body.get();
}

void WhileStmt::visit(VisitorStmt *visitor)
{
	visitor->visitWhile(this);
}

void WhileStmt::print_tree(std::ostream &os, int indent) const
{
	indent_str(os, indent);
    os << "WhileStmt: \n";
	indent_str(os, indent+1);
    os << "Condition: \n";
    condition->print_tree(os, indent + 2);
	indent_str(os, indent+1);
    os << "Body: \n";
    body->print_tree(os, indent + 2);
}

void WhileStmt::print_source(std::ostream &os, int indent) const
{
	indent_str(os, indent);
	os << "while(";
	condition->print_source(os);
	os << ")\n";
	body->print_source(os, indent + 1);
}