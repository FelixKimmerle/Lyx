#include "Parser.hpp"
#include "Expr/BinaryExpr.hpp"
#include "Expr/UnaryExpr.hpp"
#include "Expr/NumberExpr.hpp"
#include "Expr/BooleanExpr.hpp"
#include "Expr/GroupingExpr.hpp"
#include "Expr/ExplicitCastExpr.hpp"
#include "Expr/VarExpr.hpp"
#include "Expr/AssignExpr.hpp"
#include "Expr/CallExpr.hpp"

#include "Stmt/BlockStmt.hpp"
#include "Stmt/PrintStmt.hpp"
#include "Stmt/VarStmt.hpp"
#include "Stmt/IfStmt.hpp"
#include "Stmt/ForStmt.hpp"
#include "Stmt/WhileStmt.hpp"
#include "Stmt/ExprStmt.hpp"
#include "Stmt/FuncDecl.hpp"
#include "Stmt/ReturnStmt.hpp"

#include "Datatypes/DatatypePod.hpp"

#include <iostream>
#include <sstream>



bool Parser::match(const std::vector<Token::TokenType> &types)
{
	for (auto &&type : types)
	{
		if (check(type))
		{
			advance();
			return true;
		}
	}
	return false;
}
bool Parser::match(const Token::TokenType &type)
{
	if (check(type))
	{
		advance();
		return true;
	}
	return false;
}
bool Parser::check(const Token::TokenType &token_type)
{
	if (is_at_end())
	{
		return false;
	}
	return current.get_type() == token_type;
}
bool Parser::check_next(const Token::TokenType &token_type)
{
	if (is_at_end())
	{
		return false;
	}
	if (last.get_type() == Token::TokenType::TOKEN_EOF)
	{
		return false;
	}
	return last.get_type() == token_type;
}
bool Parser::is_at_end()
{
	return current.get_type() == Token::TokenType::TOKEN_EOF;
}

Token Parser::advance()
{
	if (!is_at_end())
	{
		last = current;
		current = scanner.scanToken();
	}
	return last;
}
Token Parser::consume(Token::TokenType token_type, const std::string &message)
{
	if (check(token_type))
	{
		return advance();
	}
	error(current, message);
	return current;
}

DatatypePtr Parser::token_to_datatype(Token::TokenType token_type)
{
	switch (token_type)
	{
	case Token::TokenType::TOKEN_BOOL:
		return std::make_unique<DatatypePod>(DatatypePod::PodType::BOOL);
	case Token::TokenType::TOKEN_INT64:
		return std::make_unique<DatatypePod>(DatatypePod::PodType::INT64);
	case Token::TokenType::TOKEN_FLOAT:
		return std::make_unique<DatatypePod>(DatatypePod::PodType::FLOAT);
	case Token::TokenType::TOKEN_UINT64:
		return std::make_unique<DatatypePod>(DatatypePod::PodType::UINT64);
	default:
		std::cout << "Token is not a datatype!" << std::endl;
		break;
	}
    return nullptr;
}

bool Parser::match_datatype()
{
	return match({Token::TokenType::TOKEN_BOOL,
				  Token::TokenType::TOKEN_FLOAT,
				  Token::TokenType::TOKEN_INT64,
				  Token::TokenType::TOKEN_UINT64});
}

std::unique_ptr<Expr> Parser::expression()
{
	std::unique_ptr<Expr> expr = logicalor();

	return expr;
}

std::unique_ptr<Expr> Parser::logicalor()
{
	std::unique_ptr<Expr> expr = logicaland();

	while (match(Token::TokenType::TOKEN_OR))
	{
		Token op = last;
		std::unique_ptr<Expr> right = logicaland();
		expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::OR, op.get_sector());

	}
	return expr;
}
std::unique_ptr<Expr> Parser::logicaland()
{
	std::unique_ptr<Expr> expr = equality();

	while (match(Token::TokenType::TOKEN_AND))
	{
		Token op = last;
		std::unique_ptr<Expr> right = equality();
		expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::AND, op.get_sector());
	}
	return expr;
}
std::unique_ptr<Expr> Parser::equality()
{
	std::unique_ptr<Expr> expr = comparison();

	while (match({Token::TokenType::TOKEN_BANG_EQUAL, Token::TokenType::TOKEN_EQUAL_EQUAL}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = comparison();

		if (op.get_type() == Token::TokenType::TOKEN_EQUAL_EQUAL)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BinaryOperator::EQUAL, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_BANG_EQUAL)
		{
			expr = std::make_unique<UnaryExpr>(std::make_unique<BinaryExpr>(std::move(expr), std::move(right),
																				BinaryExpr::BinaryOperator::EQUAL, op.get_sector()),
											   UnaryExpr::UnaryOperator::BANG, op.get_sector());
		}
	}
	return expr;
}
std::unique_ptr<Expr> Parser::comparison()
{
	std::unique_ptr<Expr> expr = addition();

	while (match({Token::TokenType::TOKEN_GREATER,
				  Token::TokenType::TOKEN_GREATER_EQUAL,
				  Token::TokenType::TOKEN_LESS,
				  Token::TokenType::TOKEN_LESS_EQUAL}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = addition();

		if (op.get_type() == Token::TokenType::TOKEN_GREATER)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BinaryOperator::GREATER, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_LESS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BinaryOperator::LESS, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_GREATER_EQUAL)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BinaryOperator::GREATER_EQUAL, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_LESS_EQUAL)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::BinaryOperator::LESS_EQUAL, op.get_sector());
		}
	}
	return expr;
}

std::unique_ptr<Expr> Parser::addition()
{
	std::unique_ptr<Expr> expr = multiplication();

	while (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_PLUS}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = addition();

		if (op.get_type() == Token::TokenType::TOKEN_MINUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::SUB, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_PLUS)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::ADD, op.get_sector());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::multiplication()
{
	std::unique_ptr<Expr> expr = unary();

	while (match({Token::TokenType::TOKEN_SLASH, Token::TokenType::TOKEN_STAR}))
	{
		Token op = last;
		std::unique_ptr<Expr> right = unary();

		if (op.get_type() == Token::TokenType::TOKEN_SLASH)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::DIV, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_STAR)
		{
			expr = std::make_unique<BinaryExpr>(std::move(expr), std::move(right), BinaryExpr::MUL, op.get_sector());
		}
	}

	return expr;
}
std::unique_ptr<Expr> Parser::unary()
{
	if (match({Token::TokenType::TOKEN_MINUS, Token::TokenType::TOKEN_BANG}) || match_datatype())
	{
		Token op = last;
		if (op.get_type() == Token::TokenType::TOKEN_MINUS)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::MINUS, op.get_sector());
		}
		else if (op.get_type() == Token::TokenType::TOKEN_BANG)
		{
			return std::make_unique<UnaryExpr>(std::move(unary()), UnaryExpr::BANG, op.get_sector());
		}
		else
		{
			consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' between cast and expression.");
			std::unique_ptr<Expr> right = unary();
			consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after cast.");
			return std::make_unique<ExplicitCastExpr>(std::move(right), token_to_datatype(op.get_type()), op.get_sector());
		}
	}

	return call();
}

std::unique_ptr<Expr> Parser::finish_call(std::unique_ptr<Expr> callee)
{
	std::vector<std::unique_ptr<Expr>> args;

	std::unique_ptr<CallExpr> call_expr = std::make_unique<CallExpr>(std::move(callee), last.get_sector());

	if (!match(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		do
		{
			call_expr->add_param(std::move(expression()));
		} while (match(Token::TokenType::TOKEN_COMMA));
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after function args.");
	}
	return call_expr;
}

std::unique_ptr<Expr> Parser::call()
{
	std::unique_ptr<Expr> expr = literal();

	while (true)
	{
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			expr = finish_call(std::move(expr));
		}
		else
		{
			break;
		}
	}

	return expr;
}

std::unique_ptr<Expr> Parser::literal()
{
	if (match(Token::TokenType::TOKEN_FALSE))
	{
		return std::make_unique<BooleanExpr>(false, last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_TRUE))
	{
		return std::make_unique<BooleanExpr>(true, last.get_sector());
	}
    if (match(Token::TokenType::TOKEN_NUMBER_FLOAT))
	{
		return std::make_unique<NumberExpr<float>>(static_cast<float>(std::stol(last.get_lexeme())), last.get_sector());
	}
    if (match(Token::TokenType::TOKEN_NUMBER_INT))
	{
		return std::make_unique<NumberExpr<int64_t>>(static_cast<int32_t>(std::stol(last.get_lexeme())), last.get_sector());
	}
	/*if (match(Token::TokenType::TOKEN_NUMBER_BYTE))
	{
		return std::make_unique<NumberExpr<int8_t>>(static_cast<uint8_t>(std::stol(last.get_lexeme())), last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_SHORT))
	{
		return std::make_unique<NumberExpr<int16_t>>(static_cast<int16_t>(std::stol(last.get_lexeme())), last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_INT))
	{
		return std::make_unique<NumberExpr<int32_t>>(static_cast<int32_t>(std::stol(last.get_lexeme())), last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_FLOAT))
	{
		return std::make_unique<NumberExpr<float>>(static_cast<float>(std::stol(last.get_lexeme())), last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_DOUBLE))
	{
		return std::make_unique<NumberExpr<double>>(static_cast<double>(std::stol(last.get_lexeme())), last.get_sector());
	}
	if (match(Token::TokenType::TOKEN_NUMBER_LONG))
	{
		return std::make_unique<NumberExpr<int64_t>>(static_cast<int64_t>(std::stol(last.get_lexeme())), last.get_sector());
	}
    */
	if (match(Token::TokenType::TOKEN_LEFT_PAREN))
	{
		std::unique_ptr<Expr> expr = expression();
		consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after expression.");
		return std::make_unique<GroupingExpr>(std::move(expr), expr->get_sector());
	}
	if (match(Token::TokenType::TOKEN_IDENTIFIER))
	{
		Token name = last;
		if (match(Token::TokenType::TOKEN_EQUAL))
		{
			std::unique_ptr<VarExpr> var = std::make_unique<VarExpr>(name.get_lexeme(), name.get_sector());
			std::unique_ptr<Expr> assignexpr = expression();
			/*
			if (assignexpr->resultingType() != var->resultingType())
			{
				error(&name, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(var->resultingType()) + ") and assignment: (" + lixDatatypeToString(assignexpr->resultingType()) + ") does not match.");
			}
			*/
			return std::make_unique<AssignExpr>(std::move(var), std::move(assignexpr), name.get_sector());
		}
		else
		{
			return std::make_unique<VarExpr>(name.get_lexeme(), name.get_sector());
		}
	}
	error(current, "Expect expression.");
	return nullptr;
}

std::unique_ptr<BlockStmt> Parser::block(bool constructed)
{
	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(last.get_sector(), constructed);
	while (!check(Token::TokenType::TOKEN_RIGHT_BRACE) && !is_at_end())
	{
		std::unique_ptr<Stmt> stmt = declaration();
		if (stmt != nullptr)
		{
			block_stmt->add(std::move(stmt));
		}
	}
	return block_stmt;
}

std::unique_ptr<Stmt> Parser::declaration()
{
	if (match_datatype())
	{
		DatatypePtr type = token_to_datatype(last.get_type());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		if (match(Token::TokenType::TOKEN_LEFT_PAREN))
		{
			return fun_declaration(std::move(type), name);
		}
		else
		{
			return var_declaration(std::move(type), name);
		}
	}
	if (panic_mode)
	{
		panic_mode = false;
		synchronize();
		return nullptr;
	}
	return statement();
}

std::unique_ptr<Stmt> Parser::var_declaration(DatatypePtr type, Token name)
{
	std::unique_ptr<Expr> initializer = nullptr;
	if (match(Token::TokenType::TOKEN_EQUAL))
	{
		initializer = expression();
		/*
		if (initializer->resultingType() != type)
		{
			error(&*m_Current, "Type of variable: " + name.getLexeme() + " (" + lixDatatypeToString(type) + ") and initializer: (" + lixDatatypeToString(initializer->resultingType()) + ") does not match.");
		}
		*/
	}
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after variable declaration.");
	//addVar(Variable(type, name.getLexeme(), m_uiCurrentDepth));
	return std::make_unique<VarStmt>(name.get_lexeme(), std::move(type), std::move(initializer), name.get_sector());
}

std::unique_ptr<Stmt> Parser::fun_declaration(DatatypePtr type, Token name)
{
	std::vector<std::pair<DatatypePtr, std::string>> args;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		do
		{
			if (match_datatype())
			{
				DatatypePtr type = token_to_datatype(last.get_type());
				if (match(Token::TokenType::TOKEN_IDENTIFIER))
				{
					std::string name = last.get_lexeme();
					args.push_back(std::make_pair(std::move(type), name));
				}
			}
		} while (match(Token::TokenType::TOKEN_COMMA));
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after function header.");
	consume(Token::TokenType::TOKEN_LEFT_BRACE, "Expect '{' after function header.");
	std::unique_ptr<BlockStmt> body = block(false);
	consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}' after function.");
	return std::make_unique<FuncDecl>(name.get_lexeme(), std::move(type), std::move(body), name.get_sector());
}

std::unique_ptr<Stmt> Parser::return_stmt()
{
	SourceSector position = last.get_sector();
	std::unique_ptr<Expr> expr = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<ReturnStmt>(std::move(expr), position);
}

std::unique_ptr<Stmt> Parser::statement()
{
	if (match(Token::TokenType::TOKEN_PRINT))
	{
		return print_statement();
	}
	if (match(Token::TokenType::TOKEN_LEFT_BRACE))
	{
		std::unique_ptr<Stmt> result = block(false);
		consume(Token::TokenType::TOKEN_RIGHT_BRACE, "Expected closing '}'.");
		return result;
	}
	if (match(Token::TokenType::TOKEN_IF))
	{
		return if_statement();
	}
	if (match(Token::TokenType::TOKEN_WHILE))
	{
		return while_statement();
	}
	if (match(Token::TokenType::TOKEN_FOR))
	{
		return for_statement();
	}
	if (match(Token::TokenType::TOKEN_RETURN))
	{
		return return_stmt();
	}
	return expression_statement();
}

std::unique_ptr<Stmt> Parser::print_statement()
{
	SourceSector position = last.get_sector();
	std::unique_ptr<Expr> value = expression();
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return std::make_unique<PrintStmt>(std::move(value), position);
}

std::unique_ptr<Stmt> Parser::if_statement()
{
	SourceSector position = last.get_sector();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'if'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> then = statement();
	std::unique_ptr<Stmt> elsestmt = nullptr;
	if (match(Token::TokenType::TOKEN_ELSE))
	{
		elsestmt = statement();
	}
	return std::make_unique<IfStmt>(std::move(condition), std::move(then), std::move(elsestmt), position);
}

std::unique_ptr<Stmt> Parser::while_statement()
{
	SourceSector position = last.get_sector();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'while'.");
	std::unique_ptr<Expr> condition = expression();
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after condition.");
	std::unique_ptr<Stmt> body = statement();

	return std::make_unique<WhileStmt>(std::move(condition), std::move(body), position);
}

std::unique_ptr<Stmt> Parser::for_statement()
{
	SourceSector position = last.get_sector();
	consume(Token::TokenType::TOKEN_LEFT_PAREN, "Expect '(' after 'for'.");
	std::unique_ptr<Stmt> initializer = nullptr;
	if (match(Token::TokenType::TOKEN_SEMICOLON))
	{
	}
	else if (match_datatype())
	{
		DatatypePtr type = token_to_datatype(last.get_type());
		Token name = consume(Token::TokenType::TOKEN_IDENTIFIER, "Expect name.");
		initializer = var_declaration(std::move(type), name);
	}
	else
	{
		initializer = expression_statement();
	}

	std::unique_ptr<Expr> condition = nullptr;
	if (!check(Token::TokenType::TOKEN_SEMICOLON))
	{
		condition = expression();
	}
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after loop condition.");

	std::unique_ptr<Expr> increment = nullptr;
	if (!check(Token::TokenType::TOKEN_RIGHT_PAREN))
	{
		increment = expression();
	}
	consume(Token::TokenType::TOKEN_RIGHT_PAREN, "Expect ')' after for clauses.");

	std::unique_ptr<Stmt> body = statement();

	std::unique_ptr<BlockStmt> block_stmt = std::make_unique<BlockStmt>(position);
	block_stmt->add(std::move(std::make_unique<ForStmt>(std::move(condition), std::move(body), std::move(initializer), std::move(increment), position)));
	return block_stmt;
}

std::unique_ptr<Stmt> Parser::expression_statement()
{
	std::unique_ptr<Expr> expr = expression();
	std::unique_ptr<ExprStmt> exprstmt = std::make_unique<ExprStmt>(std::move(expr), expr->get_sector());
	consume(Token::TokenType::TOKEN_SEMICOLON, "Expect ';' after expression.");
	return exprstmt;
}

void Parser::error(const Token &token, const std::string &message)
{
	encountered_error = true;
	panic_mode = true;

	std::stringstream ss;
	ss << token.get_sector();


    std::cout << "Error at: " << token.get_sector() << ". " << message << std::endl;
}

void Parser::synchronize()
{
	while (current.get_type() != Token::TokenType::TOKEN_EOF)
	{
		if (last.get_type() == Token::TokenType::TOKEN_SEMICOLON)
		{
			return;
		}
		switch (current.get_type())
		{
		case Token::TokenType::TOKEN_CLASS:
		case Token::TokenType::TOKEN_FUN:
		case Token::TokenType::TOKEN_VAR:
		case Token::TokenType::TOKEN_FOR:
		case Token::TokenType::TOKEN_IF:
		case Token::TokenType::TOKEN_WHILE:
		case Token::TokenType::TOKEN_PRINT:
		case Token::TokenType::TOKEN_RETURN:
			return;
		default:
			break;
		}
		advance();
	}
}

StmtPtr Parser::parse()
{
	advance();
	std::unique_ptr<BlockStmt> statements = std::make_unique<BlockStmt>(SourceSector());
	while (!is_at_end())
	{
		std::unique_ptr<Stmt> stmt = declaration();
		if (stmt != nullptr)
		{
			statements->add(std::move(stmt));
		}
	}
	return statements;
}

bool Parser::had_error()
{
	return encountered_error;
}

Parser::Parser(const std::string &file_name, const std::string &src) : scanner(file_name,src), encountered_error(false), panic_mode(false)
{
}

Parser::Parser(const std::string &file_name) : scanner(file_name), encountered_error(false), panic_mode(false)
{
    
}