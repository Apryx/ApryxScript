#pragma once

#include <memory>
#include <vector>
#include "lexer/Lexer.h"

namespace apryx {

	class Expression;
	class Statement;
	class Function;
	class Variable;
	class Structure;
	class Context;

	class Parser {

	public:
		std::shared_ptr<Statement> parseStatement(Lexer &lexer);
	public:
		std::shared_ptr<Expression> parseExpression(Lexer &lexer, int detail = 4);
		std::shared_ptr<Expression> parseExpressionSimple(Lexer &lexer);
		std::shared_ptr<Function> parseFunction(Lexer &lexer);
		std::shared_ptr<Variable> parseVariable(Lexer &lexer);
		std::shared_ptr<Structure> parseStructure(Lexer &lexer);

		bool parseType(Lexer &lexer, std::string &out);
	private:

		void unexpectedToken(Lexer &lexer, Token::Type expected);
		void unexpectedToken(Lexer &lexer);
	};
}