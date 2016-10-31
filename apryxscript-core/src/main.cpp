//TODO move this to different project (apryxscript-application)

#include "logger/log.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Statement.h"
#include "runtime/Runtime.h"

#include "tests/ParserTest.h"

#include <memory>
#include <fstream>
#include <sstream>

int main(void)
{
	apryx::testParser();
	WAIT();
	return 0;
}