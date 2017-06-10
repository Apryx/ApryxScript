//TODO move this to different project (apryxscript-application)

#include "logger/log.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Statement.h"

#include "tests/ParserTest.h"

#include <memory>
#include <fstream>
#include <sstream>

int main(void)
{
	/*
	apryx::testTypes();
	apryx::testParserToDecoratedAST();
	apryx::testModifiers();
	apryx::testLexer();
	apryx::testParser();
	*/

	apryx::testFile("test.apx");

	WAIT();
	return 0;
}