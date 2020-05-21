#pragma once

#include <memory>
#include <vector>

#include "lexer/Lexer.h"

#include "ast/ast.h"

namespace apryx {

	//class Expression;
	//class Statement;
	//class FunctionStatement;
	//class VariableStatement;
	//class StructureStatement;
	//class BlockStatement;
	//class Context;
	//class CompilationUnit;

	class Parser {

	public:
		//Use this one only. The other things are reserved
		std::shared_ptr<Statement>	parseStatement(Lexer &lexer);
		std::shared_ptr<CompilationUnit> parseAll(Lexer &lexer);
	public:
		std::shared_ptr<FunctionStatement>	parseFunction(Lexer &lexer, std::vector<Token> modifiers);
		std::shared_ptr<VariableStatement>	parseVariable(Lexer &lexer, std::vector<Token> modifiers);
		std::shared_ptr<StructureStatement>	parseStructure(Lexer &lexer, std::vector<Token> modifiers);

		std::shared_ptr<NamespaceStatement>	parseNamespace(Lexer &lexer);
		std::shared_ptr<IncludeStatement>	parseInclude(Lexer &lexer);

		std::shared_ptr<Expression>	parseExpression(Lexer &lexer, int detail = 7);
		std::shared_ptr<Expression> parseExpressionSimple(Lexer &lexer);
		std::shared_ptr<BlockStatement> parseBlock(Lexer &lexer);

		std::shared_ptr<NameAndType> parseNameAndType(Lexer &lexer);
		std::shared_ptr<NamedType> parseNamedType(Lexer &lexer);
	private:
		void unexpectedToken(Lexer &lexer, Token::Type expected);
		void unexpectedToken(Lexer &lexer);
	};
}