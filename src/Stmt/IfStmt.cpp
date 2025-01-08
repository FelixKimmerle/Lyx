#include "IfStmt.hpp"
#include "VisitorStmt.hpp"
IfStmt::IfStmt(ExprPtr condition, StmtPtr then_body, StmtPtr else_body, SourceSector position) : Stmt(position),
																								  condition(std::move(condition)),
																								  then_body(std::move(then_body)),
																								  else_body(std::move(else_body))

{
}

void IfStmt::visit(VisitorStmt *visitor)
{
	visitor->visitIf(this);
}

Expr *IfStmt::get_condition()
{
	return condition.get();
}

Stmt *IfStmt::get_then()
{
	return then_body.get();
}

Stmt *IfStmt::get_else()
{
	return else_body.get();
}

void IfStmt::print_tree(std::ostream &os, int indent) const
{
	indent_str(os, indent);
    os << "IfStmt: \n";
	indent_str(os, indent);
    os << "Condition: \n";
	condition->print_tree(os, indent + 1);
	indent_str(os, indent);
    os << "Then: \n";
	then_body->print_tree(os, indent + 1);
	if(else_body != nullptr)
	{
		indent_str(os, indent);
    	os << "Else: \n";
		else_body->print_tree(os, indent + 1);
	}
}

void IfStmt::print_source(std::ostream &os, int indent) const
{
	indent_str(os, indent);
	os << "if(";
	condition->print_source(os);
	os << ")\n";
	then_body->print_source(os, indent + 1);
	if(else_body != nullptr)
	{
		os << "\n";
		indent_str(os, indent);
		os << "else\n";
		else_body->print_source(os, indent + 1);
	}
}
