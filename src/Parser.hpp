#pragma once

#include "Scanner.hpp"
#include "Expr/Expr.hpp"
#include "Expr/VarExpr.hpp"
#include "Stmt/Stmt.hpp"
#include "Stmt/BlockStmt.hpp"
#include "Datatypes/Datatype.hpp"

#include <list>
#include <memory>

class Parser
{
private:
    Scanner scanner;
    bool match(const std::vector<Token::TokenType> &types);
    bool match(const Token::TokenType &type);
    bool check(const Token::TokenType &token_type);
    bool check_next(const Token::TokenType &token_type);
    bool is_at_end();
    Token advance();
    Token consume(Token::TokenType token_type, const std::string &message);
    DatatypePtr token_to_datatype(Token::TokenType token_type);
    bool match_datatype();

    std::unique_ptr<Expr> expression();
    std::unique_ptr<Expr> logicalor();
    std::unique_ptr<Expr> logicaland();
    std::unique_ptr<Expr> equality();
    std::unique_ptr<Expr> comparison();
    std::unique_ptr<Expr> addition();
    std::unique_ptr<Expr> multiplication();
    std::unique_ptr<Expr> unary();
    std::unique_ptr<Expr> call();
    std::unique_ptr<Expr> finish_call(std::unique_ptr<Expr> callee);
    std::unique_ptr<Expr> literal();

    std::unique_ptr<BlockStmt> block();
    std::unique_ptr<Stmt> declaration();
    std::unique_ptr<Stmt> var_declaration(DatatypePtr type, Token name);
    std::unique_ptr<Stmt> statement();
    std::unique_ptr<Stmt> print_statement();
    std::unique_ptr<Stmt> if_statement();
    std::unique_ptr<Stmt> while_statement();
    std::unique_ptr<Stmt> for_statement();
    std::unique_ptr<Stmt> fun_declaration(DatatypePtr type, Token name);
    std::unique_ptr<Stmt> return_stmt();
    std::unique_ptr<Stmt> expression_statement();

    Token current;
    Token last;

    bool encountered_error;
    bool panic_mode;
    void error(const Token &token, const std::string &message);
    void synchronize();

public:
    Parser(const std::string &file_name, const std::string &src);
    Parser(const std::string &file_name);
    std::unique_ptr<BlockStmt> parse();
    bool had_error();
};