#include "ForStmt.hpp"
#include "VisitorStmt.hpp"

ForStmt::ForStmt(ExprPtr condition, StmtPtr body, StmtPtr initializer, ExprPtr increment, SourceSector position) : Stmt(position),
																															   condition(std::move(condition)),
																															   body(std::move(body)),
																															   initializer(std::move(initializer)),
																															   increment(std::move(increment))
{
}

Expr *ForStmt::get_condition()
{
	return condition.get();
}

Stmt *ForStmt::get_body()
{
	return body.get();
}

Stmt *ForStmt::get_initializer()
{
	return initializer.get();
}

Expr *ForStmt::get_increment()
{
	return increment.get();
}

void ForStmt::visit(VisitorStmt *visitor)
{
	visitor->visitFor(this);
}

void ForStmt::print_tree(std::ostream &os, int indent) const
{
	indent_str(os, indent);
    os << "ForStmt:";
	indent_str(os, indent);
    os << "Init: \n";
    initializer->print_tree(os, indent + 1);
	indent_str(os, indent);
    os << "Condition: \n";
    condition->print_tree(os, indent + 1);
	indent_str(os, indent);
    os << "Increment: \n";
    increment->print_tree(os, indent + 1);
	indent_str(os, indent);
    os << "Body: \n";
    body->print_tree(os, indent + 1);
}

void ForStmt::print_source(std::ostream &os, int indent) const
{
	indent_str(os, indent);
	os << "for(";
	initializer->print_source(os);
	condition->print_source(os);
	os << "; ";
	increment->print_source(os);
	os << ")\n";
	body->print_source(os, indent + 1);
}
