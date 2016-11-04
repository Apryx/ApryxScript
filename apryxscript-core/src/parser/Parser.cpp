#include "Parser.h"

#include "ast/Expression.h"
#include "ast/Statement.h"
#include "lexer/Lexer.h"
#include "logger/log.h"

//TODO document which function consumes what tokens

namespace apryx {

	std::shared_ptr<Function> Parser::parseFunction(Lexer & lexer)
	{
		if (lexer.current().m_Data != "function") {
			unexpectedToken(lexer);
			return nullptr;
		}
		auto function = std::make_shared<Function>();

		if (lexer.next().m_Type != Token::IDENTIFIER){
			unexpectedToken(lexer, Token::IDENTIFIER);
			return nullptr;
		}

		function->m_Name = lexer.current().m_Data;

		if (lexer.next().m_Type != Token::OPEN_BRACKET) {
			unexpectedToken(lexer, Token::OPEN_BRACKET);
			return nullptr;
		}

		if (lexer.next().m_Type != Token::CLOSE_BRACKET) {
			function->m_Arguments = parseExpression(lexer);
			if (lexer.current().m_Type != Token::CLOSE_BRACKET) {
				unexpectedToken(lexer, Token::CLOSE_BRACKET);
				return nullptr;
			}
		}

		//Consume )
		lexer.next();

		if (lexer.current().m_Type == Token::COLON) {
			//Consume the :
			lexer.next();
			if (auto s = parseType(lexer)) {
				function->m_ReturnType = *s;
			} else {
				unexpectedToken(lexer);
				return nullptr;
			}
		}
		else {
			function->m_ReturnType = "void";
		}

		function->m_Statement = parseStatement(lexer);

		return function;
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
			if (auto s = parseType(lexer)) {
				var->m_Type = *s;
			} else {
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
		//If its a block
		else if (lexer.current().m_Type == Token::OPEN_CURLY) {
			return parseBlock(lexer);
		}
		else if (lexer.current().m_Type == Token::LINE_END) {
			lexer.next();
			//Yes, we do completely ignore line ends, they mean basically nothing. The only thing there are really good for is expression seperation, and that
			//works just fine with this current system e.g. a + b; a + b; . However a + b a + b is just as valid.
			return parseStatement(lexer);
		}
		//Else, it basically always is an expression
		else {
			if (auto e = parseExpression(lexer)) {
				auto statement = std::make_shared<ExpressionStatement>();
				statement->m_Expression = e;
				return statement;
			}
			else {
				unexpectedToken(lexer);
				return nullptr;
			}
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

			while (lexer.current().m_Type == Token::OPERATOR_LOOKUP || lexer.current().m_Type == Token::OPEN_BRACKET) {

				if (lexer.current().m_Type == Token::OPERATOR_LOOKUP) {
					lexer.next();
					auto rhs = parseExpression(lexer, detail - 1);

					auto exp = std::make_shared<LookupExpression>();

					exp->m_Lhs = lhs;
					exp->m_Rhs = rhs;
					
					lhs = exp;
				}
				else if (lexer.current().m_Type == Token::OPEN_BRACKET) {
					auto exp = std::make_shared<InvokeExpression>();

					exp->m_Lhs = lhs;
					exp->m_Token = lexer.current();

					if (lexer.next().m_Type != Token::CLOSE_BRACKET) {
						auto rhs = parseExpression(lexer); //Parse a full expression between these brackets
						exp->m_Args = rhs;
						if (lexer.current().m_Type != Token::CLOSE_BRACKET) {
							unexpectedToken(lexer);
						}
					}

					//Consume the closing bracket
					lexer.next();

					lhs = exp;
				}
			}

			return lhs;
		}

		//--------------------------------------------------------------//
		// Prefix operators
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

			while (lexer.current().m_Type == Token::OPERATOR_MULTIPLY
				|| lexer.current().m_Type == Token::OPERATOR_DIVIDE
				|| lexer.current().m_Type == Token::OPERATOR_MOD) {

				auto exp = std::make_shared<OperatorExpression>();
				exp->m_Lhs = lhs;
				exp->m_Operator = lexer.current().m_Data;

				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail - 1);

				lhs = exp;
			}

			return lhs;
		}

		//--------------------------------------------------------------//
		// Adding and subtracting
		//--------------------------------------------------------------//
		else if (detail == 4) {
			auto lhs = parseExpression(lexer, detail - 1);

			while (lexer.current().m_Type == Token::OPERATOR_ADD
				|| lexer.current().m_Type == Token::OPERATOR_SUBTRACT) {
				auto exp = std::make_shared<OperatorExpression>();
				exp->m_Lhs = lhs;
				exp->m_Operator = lexer.current().m_Data;
				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail - 1);

				lhs = exp;
			}

			return lhs;
		}

		//--------------------------------------------------------------//
		// Assignment
		//--------------------------------------------------------------//
		else if (detail == 5) {
			auto lhs = parseExpression(lexer, detail - 1);

			if (lexer.current().m_Type == Token::OPERATOR_EQUALS) {

				auto exp = std::make_shared<OperatorExpression>();
				exp->m_Lhs = lhs;
				exp->m_Operator = lexer.current().m_Data;
				lexer.next();
				exp->m_Rhs = parseExpression(lexer, detail);

				return exp;
			}

			return lhs;
		}

		//--------------------------------------------------------------//
		// Seperator
		//--------------------------------------------------------------//
		else if (detail == 6) {
			
			auto lhs = parseExpression(lexer, detail - 1);
			
			if (lexer.current().m_Type == Token::SEPERATOR) {
				auto exp = std::make_shared<ListExpression>();

				exp->m_List.push_back(lhs);

				while (lexer.current().m_Type == Token::SEPERATOR) {
					lexer.next();

					auto e = parseExpression(lexer, detail - 1);

					exp->m_List.push_back(e);
				}

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
		if (lexer.current().m_Type == Token::FLOAT) {
			auto exp = std::make_shared<ConstantExpression>(lexer.current().m_Data);
			exp->m_Token = lexer.current();
			exp->m_Type = ConstantExpression::FLOAT;
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

	std::shared_ptr<Block> Parser::parseBlock(Lexer & lexer)
	{
		if (lexer.current().m_Type != Token::OPEN_CURLY) {
			unexpectedToken(lexer, Token::OPEN_CURLY);
			return nullptr;
		}

		auto block = std::make_shared<Block>();

		//Consume {
		lexer.next();

		while (lexer && lexer.current().m_Type != Token::CLOSE_CURLY) {
			auto s = parseStatement(lexer);
			
			if(s)
				block->m_Statements.push_back(s);
		}

		return block;
	}

	boost::optional<std::string> Parser::parseType(Lexer & lexer)
	{
		if (lexer.current().m_Type == Token::IDENTIFIER) {
			std::string data = lexer.current().m_Data;
			lexer.next();
			return data;
		}
		else {
			return boost::none;
		}
	}
}
