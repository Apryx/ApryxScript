#pragma once

#include <string>

namespace apryx {
	void testLexer();
	void testParser();

	void testExpressionGenerator();

	void testTypes();

	void testDecoratedAST();

	void testParserToDecoratedAST();

	void testModifiers();

	void testFile(const std::string &filename);
}