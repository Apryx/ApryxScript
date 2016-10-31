#include "ParserTest.h"

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Expression.h"

#include <sstream>
#include "logger/log.h"

namespace apryx {

	static std::shared_ptr<std::istringstream> getExpressionTest(std::string input)
	{
		return std::make_shared<std::istringstream>(
			std::move(input)
			);
	}
	static std::shared_ptr<std::istringstream> getTestLexer()
	{
		return std::make_shared<std::istringstream>(
			"1 1.1 1.1f 1.1d 1l 2f 2d 2 \n"		//Numbers
			"a \"b\" var\n"						//Identifiers, literals and keywords
			";\n"								//Line end
			"()[]{}\n"							//Parenthesis
			"+ - * / % . ! :: , ++ --\n"		//Operators
			">> << ~ | & ^\n"					//Bitwise operators //TODO ^ power or bitwisexor
			"> < >= <= == != \n"				//Comparators
			">|| && \n"							//Logical operators
			"= += -= *= /= %= \n"				//Assignments
			"new in \n"							//Keyword operators
			);
	}

	void testLexer()
	{
		Lexer lexer(getTestLexer());

		while (lexer.next())
			LOG(lexer.current());
	}

	static void performTest(std::string test) 
	{
		LOG("Test start \t " << test << " ");

		Parser parser;

		Lexer lexer(getExpressionTest(test));
		lexer.next();
		auto a = parser.parseExpression(lexer);
		if (a) {
			LOG(a->toString());
		}
		else {
			LOG_ERROR("Result was null");
		}
		LOG("Test done. " << std::endl);
	}

	void testParser()
	{
		LOG("Simple expressions");
		performTest("a + b * c");

		performTest("a * b + c");

		performTest("a + b + c");

		performTest("a . b . c");

		LOG("Invocations");

		performTest("print()");

		performTest("print(a)");

		performTest("print(a + b * c)");

		performTest("a.b()");

		performTest("a.b().c()");
		performTest("a.b().c()()"); //Hardest of hardcore

		LOG("Prefix operators");

		performTest("!a");

		performTest("!!a");

		performTest("-a");

		performTest("a * !b + -c");


		
	}
}
