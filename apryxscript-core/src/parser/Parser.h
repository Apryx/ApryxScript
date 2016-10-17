#pragma once

#include <memory>
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
	private:
		std::shared_ptr<Expression> parseExpression(Lexer &lexer);
		std::shared_ptr<Expression> parseExpressionSimple(Lexer &lexer);
		std::shared_ptr<Function> parseFunction(Lexer &lexer);
		std::shared_ptr<Variable> parseVariable(Lexer &lexer);
		std::shared_ptr<Structure> parseStructure(Lexer &lexer);

		bool parseType(Lexer &lexer, std::string &out);

		void unexpectedToken(Lexer &lexer, Token::Type expected);
		void unexpectedToken(Lexer &lexer);
	};
}