#pragma once

#include <memory>
#include <vector>
#include <boost/optional.hpp>
#include "lexer/Lexer.h"

namespace apryx {

	class Expression;
	class Statement;
	class Function;
	class Variable;
	class Structure;
	class Block;
	class Context;

	class Parser {

	public:
		//Use this one only. The other things are reserved
		std::shared_ptr<Statement>	parseStatement(Lexer &lexer);
		std::shared_ptr<Block>		parseAll(Lexer &lexer);

	public:
		std::shared_ptr<Function>	parseFunction(Lexer &lexer, std::vector<Token> modifiers);
		std::shared_ptr<Variable>	parseVariable(Lexer &lexer, std::vector<Token> modifiers);
		std::shared_ptr<Structure>	parseStructure(Lexer &lexer, std::vector<Token> modifiers);

		std::shared_ptr<Expression>	parseExpression(Lexer &lexer, int detail = 7);
		std::shared_ptr<Expression> parseExpressionSimple(Lexer &lexer);
		std::shared_ptr<Block>		parseBlock(Lexer &lexer);

		boost::optional<std::string> parseType(Lexer &lexer);
	private:

		void unexpectedToken(Lexer &lexer, Token::Type expected);
		void unexpectedToken(Lexer &lexer);
	};
}