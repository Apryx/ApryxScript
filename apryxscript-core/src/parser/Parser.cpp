#include "Parser.h"

#include "ast/Expression.h"
#include "ast/Statement.h"
#include "lexer/Lexer.h"
#include "debug/Debug.h"

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

	std::shared_ptr<Expression> Parser::parseExpression(Lexer & lexer)
	{
		auto lhs = parseExpressionSimple(lexer);

		if (isOperator(lexer.current())) {
			Token t = lexer.current();

			lexer.next();

			auto rhs = parseExpression(lexer);

			auto exp = std::make_shared<OperatorExpression>(lhs, rhs, t.m_Data);

			//TODO order of operations here!

			return exp;
		}
		
		else if (lexer.current().m_Type == Token::OPEN_BRACKET) {
			//Consume the (
			if (lexer.next().m_Type == Token::CLOSE_BRACKET) {
				lexer.next(); //Consume the )
				return std::make_shared<InvokeExpression>(lhs, nullptr);
			}

			auto exp = parseExpression(lexer);

			if (lexer.current().m_Type != Token::CLOSE_BRACKET) {
				unexpectedToken(lexer, Token::CLOSE_BRACKET);
				return nullptr;
			}
			lexer.next(); //Consume )

			return std::make_shared<InvokeExpression>(lhs, exp);
		}

		else if (lexer.current().m_Type == Token::SEPERATOR) {
			lexer.next(); //Consume the ,

			auto exp = parseExpression(lexer);

			//If the parsed expression is part of this list we are making
			if (auto l = std::dynamic_pointer_cast<ListExpression>(exp)) {
				//insert at the front
				l->m_Expressions.insert(l->m_Expressions.begin(), lhs);
				return l;
			}
			else {
				l = std::make_shared<ListExpression>();

				l->m_Expressions.push_back(lhs);
				l->m_Expressions.push_back(exp);

				return l;
			}
		}

		return lhs;
	}

	std::shared_ptr<Expression> Parser::parseExpressionSimple(Lexer & lexer)
	{
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
