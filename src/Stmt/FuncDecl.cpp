#include "FuncDecl.hpp"
#include "VisitorStmt.hpp"
FuncDecl::FuncDecl(std::string name, DatatypePtr return_type, std::unique_ptr<BlockStmt> body, SourceSector sector) : Stmt(sector),
                                                                                                                      body(std::move(body)),
                                                                                                                      return_type(std::move(return_type)),
                                                                                                                      name(name)
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
    args.push_back(std::make_pair(std::move(datatype),name));
}