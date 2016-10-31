#include "Parser.h"

#include "ast/Expression.h"
#include "ast/Statement.h"
#include "lexer/Lexer.h"
#include "logger/log.h"

namespace apryx {
	
	std::shared_ptr<Function> Parser::parseFunction(Lexer & lexer)
	{
		return std::shared_ptr<Function>();
	}

	std::shared_ptr<Variable> Parser::parseVariable(Lexer & lexer)
	{
		if (lexer.current().m_Data != "var") {
			unexpectedToken(lexer);
			return nullptr;
		}
		auto var = std::make_shared<Variable>();

		if (lexer.next().m_Type != Token::IDENTIFIER) {
			unexpectedToken(lexer, Token::IDENTIFIER);
			return nullptr;
		}

		var->m_Name = lexer.current().m_Data;

		lexer.next();
		if (lexer.current().m_Type == Token::COLON) {
			lexer.next();
			if (!parseType(lexer, var->m_Type)) {
				unexpectedToken(lexer);
				return nullptr;
			}
		}
		
		if (lexer.current().m_Type == Token::OPERATOR_EQUALS) {
			lexer.next();
			var->m_InitialValue = parseExpression(lexer);
		}

		if(!var->isValid()){
			unexpectedToken(lexer);
			lexer.next();
			return nullptr;
		}

		return var;
	}

	std::shared_ptr<Structure> Parser::parseStructure(Lexer & lexer)
	{
		return std::shared_ptr<Structure>();
	}

	bool Parser::parseType(Lexer & lexer, std::string & out)
	{
		if (lexer.current().m_Type == Token::IDENTIFIER) {
			out = lexer.current().m_Data;
			lexer.next();
			return true;
		}
		else {
			return false;
		}
	}

	void Parser::unexpectedToken(Lexer & lexer, Token::Type expected)
	{
		LOG_ERROR("Unexpected token : " << lexer.current() << ". Expected : " << expected);
	}

	void Parser::unexpectedToken(Lexer & lexer)
	{
		LOG_ERROR("Unexpected token : " << lexer.current());
	}

	std::shared_ptr<Statement> Parser::parseStatement(Lexer & lexer)
	{
		//If its a keyword, see what we can do
		if (lexer.current().m_Type == Token::KEYWORD) {
			if (lexer.current().m_Data == "function") {
				return parseFunction(lexer);
			}
			else if (lexer.current().m_Data == "var") {
				return parseVariable(lexer);
			}
			else if (lexer.current().m_Data == "struct" || lexer.current().m_Data == "class") {
				return parseStructure(lexer);
			}
			else {
				unexpectedToken(lexer);
				lexer.next();
				return nullptr;
			}
		}
		//Else, it basically always is an expression
		else {
			return parseExpression(lexer);
		}
		
		assert(false);
		return nullptr;
	}

	std::shared_ptr<Expression> Parser::parseExpression(Lexer & lexer, int detail)
	{
		//--------------------------------------------------------------//
		//Value types
		//--------------------------------------------------------------//
		if (detail <= 0) {
			return parseExpressionSimple(lexer);
		}
		//--------------------------------------------------------------//
		//Lookups and invocations (TODO postfix operators like ++ and --)
		//--------------------------------------------------------------//
		else if (detail == 1) {
			auto lhs = parseExpression(lexer, detail - 1);

			if (lexer.current().m_Type == Token::OPERATOR_LOOKUP) {
				lexer.next();
				auto rhs = parseExpression(lexer, detail);
				
				auto exp = std::make_shared<LookupExpression>();

				exp->m_Lhs = lhs;
				exp->m_Rhs = rhs;

				return exp;
			}
			else if (lexer.current().m_Type == Token::OPEN_BRACKET) {
				auto exp = std::make_shared<InvokeExpression>();

				exp->m_Lhs = lhs;
				exp->m_Token = lexer.current();

				if (lexer.next().m_Type != Token::CLOSE_BRACKET) {
					auto rhs = parseExpression(lexer); //Parse a full expression between these brackets
					exp->m_Args = rhs;
				}

				return exp;
			}
			else {
				return lhs;
			}
		}
		//--------------------------------------------------------------//
		// prefix operators
		//--------------------------------------------------------------//
		else if (detail == 2) {
			if (lexer.current().m_Type == Token::OPERATOR_NOT
				|| lexer.current().m_Type == Token::OPERATOR_ADD
				|| lexer.current().m_Type == Token::OPERATOR_SUBTRACT) {
				auto exp = std::make_shared<PrefixOperatorExpression>();
				exp->m_Token = lexer.current();
				exp->m_Operator = lexer.current().m_Data;
				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail);

				return exp;
			}
			else {
				return parseExpression(lexer, detail - 1);
			}
		}
		//--------------------------------------------------------------//
		// Multiplication and division
		//--------------------------------------------------------------//
		else if (detail == 3) {
			auto lhs = parseExpression(lexer, detail - 1);

			if (lexer.current().m_Type == Token::OPERATOR_MULTIPLY
				|| lexer.current().m_Type == Token::OPERATOR_DIVIDE
				|| lexer.current().m_Type == Token::OPERATOR_MOD) {

				auto exp = std::make_shared<OperatorExpression>();
				exp->m_Lhs = lhs;
				exp->m_Operator = lexer.current().m_Data;

				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail); //Parse expression with same detail level!

				return exp;
			}
			else {
				return lhs;
			}
		}

		//--------------------------------------------------------------//
		// Adding and subtracting
		//--------------------------------------------------------------//
		else if (detail == 4) {
			auto lhs = parseExpression(lexer, detail - 1);

			if (lexer.current().m_Type == Token::OPERATOR_ADD
				|| lexer.current().m_Type == Token::OPERATOR_SUBTRACT) {
				auto exp = std::make_shared<OperatorExpression>();
				exp->m_Lhs = lhs;
				exp->m_Operator = lexer.current().m_Data;
				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail); //Parse expression with same detail level!

				return exp;
			}
			else {
				return lhs;
			}
		}

		else {
			return parseExpression(lexer, detail - 1);
		}

		//This should NEVER happen
		assert(false);
	}

	std::shared_ptr<Expression> Parser::parseExpressionSimple(Lexer & lexer)
	{
		//Parenthesis
		if (lexer.current().m_Type == Token::OPEN_BRACKET) {
			lexer.next();

			auto exp = parseExpression(lexer);

			if (lexer.current().m_Type != Token::CLOSE_BRACKET) {
				unexpectedToken(lexer);
				lexer.next();
				return exp;
			}
			else {
				return exp;
			}
		}

		if (lexer.current().m_Type == Token::IDENTIFIER) {
			auto exp = std::make_shared<IdentiefierExpression>(lexer.current().m_Data);
			exp->m_Token = lexer.current();

			lexer.next();

			return exp;
		}
		if (lexer.current().m_Type == Token::INTEGER) {
			auto exp = std::make_shared<ConstantExpression>(lexer.current().m_Data);
			exp->m_Token = lexer.current();
			exp->m_Type = ConstantExpression::INT;
			lexer.next();
			return exp;
		}
		if (lexer.current().m_Type == Token::STRING) {
			auto exp = std::make_shared<ConstantExpression>(lexer.current().m_Data);
			exp->m_Token = lexer.current();
			exp->m_Type = ConstantExpression::STRING;
			lexer.next();
			return exp;
		}
		else {
			unexpectedToken(lexer);
			lexer.next();
			return nullptr;
		}
	}
}
