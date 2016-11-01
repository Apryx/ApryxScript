#include "ParserTest.h"

#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Expression.h"

#include <sstream>
#include "logger/log.h"

#include "generator/Generator.h"

#include "vm/ScriptVM.h"

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

	static void parseExpressionTest(std::string test) 
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

		parseExpressionTest("a + b * c");
		//a + (b * c)

		parseExpressionTest("a * b + c");
		//(a * b) + c

		parseExpressionTest("a + b + c");
		//(a + b) + c

		parseExpressionTest("a . b . c");
		//(a . b) . c

		parseExpressionTest("a = b = c");
		//a = (b = c)
	}

	static bool testPrint(std::vector<VMValue> &stack, int argCount)
	{
		for (int i = 0; i < argCount; i++) {
			VMValue v = stack.back();
			stack.pop_back();

			LOG(v);
		}

		return true;
	}

	void testExpressionGenerator()
	{
		Lexer lexer(std::make_shared<std::istringstream>(
			"print(1f + 3f * 2f, 3f * 3f + 2f * 2f / 6.6f)"
			));
		lexer.next();

		Parser parser;

		auto ctx = std::make_shared<Context>();

		ExpressionGenerator generator(ctx);
		auto exp = parser.parseExpression(lexer);
		exp->accept(generator);

		generator.getWriter().ret();

		ScriptVM vm;

		//Register print function
		VMValue value;
		value.setType(VMValue::Type::NATIVE_FUNCTION);
		value.m_Native = testPrint;
		vm.m_Globals->set("print", value);

		VMFunction function(generator.getWriter());

		vm.execute(function);
	}
}
