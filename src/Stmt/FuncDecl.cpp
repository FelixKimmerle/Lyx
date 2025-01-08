#include "FuncDecl.hpp"
#include "VisitorStmt.hpp"
FuncDecl::FuncDecl(std::string name, DatatypePtr return_type, std::unique_ptr<BlockStmt> body, SourceSector sector) : Stmt(sector),
                                                                                                                      name(name),
                                                                                                                      return_type(std::move(return_type)),
                                                                                                                      body(std::move(body))
{
}

void FuncDecl::visit(VisitorStmt *p_pVisitor)
{
    p_pVisitor->visitFuncDecl(this);
}

BlockStmt *FuncDecl::get_body()
{
    return body.get();
}

std::string FuncDecl::get_name() const
{
    return name;
}

Datatype *FuncDecl::get_return_type() const
{
    return return_type.get();
}

std::vector<std::pair<DatatypePtr, std::string>>::iterator FuncDecl::begin()
{
    return args.begin();
}
std::vector<std::pair<DatatypePtr, std::string>>::iterator FuncDecl::end()
{
    return args.end();
}

unsigned int FuncDecl::get_arity() const
{
    return args.size();
}

void FuncDecl::add_arg(std::string name, DatatypePtr datatype)
{
    args.push_back(std::make_pair(std::move(datatype), name));
}

void FuncDecl::print_tree(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << "FuncDecl: \n";
    indent_str(os, indent);
    os << "Parameters: \n";
    for (const auto &arg : args)
    {
        os << std::string(indent + 1, ' ') << arg.second << "\n";
    }
    indent_str(os, indent);
    os << "Body: \n";
    body->print_tree(os, indent + 1);
}

void FuncDecl::print_source(std::ostream &os, int indent) const
{
    indent_str(os, indent);
    os << name << "(";
    bool first = true;
    for (const auto &arg : args)
    {
        if (first)
        {
            first = false;
        }
        else
        {
            os << ",";
        }
        os << arg.second;
    }
    os << ")\n";
    body->print_source(os, indent + 1);
}
