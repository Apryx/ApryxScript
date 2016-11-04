#include "ParserTest.h"

#include "lexer/Lexer.h"
#include "parser/Parser.h"

#include "ast/Statement.h"
#include "ast/Expression.h"

#include <sstream>
#include "logger/log.h"

#include "generator/Generator.h"

#include "decorated_ast/ApryxClass.h"
#include "decorated_ast/ApryxFunction.h"
#include "decorated_ast/Type.h"

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

	static void parseStatementTest(std::string test)
	{
		LOG("Test start \t " << test << " ");

		Parser parser;

		Lexer lexer(getExpressionTest(test));
		lexer.next();
		auto a = parser.parseStatement(lexer);
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

		LOG("Variables");

		parseStatementTest("var a = 1");
		parseStatementTest("var a : int");

		LOG("Functions");

		parseStatementTest("function a(){}");
		parseStatementTest("function a() : int{}");

		LOG("Kinda full intergration");

		parseStatementTest(
			"function main()\n"
			"{\n"
			"var a = 1\n"
			"var b = 2\n"
			"var c = b + a * 2\n"
			"print(c)\n"
			"}"
		);


		LOG("");
		LOG("Push it to the limit!");
		parseStatementTest(
			"{a + b a + b * c + d}"
		);
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

	void testTypes()
	{
		LOG("Type test start...");

		Type ti = Type::getInt();
		Type tf = Type::getFloat();

		assert(ti == ti);
		assert(tf == tf);

		assert(!(ti == tf));

		Type c1 = Type::getClass("Object", "apryx/lang");
		Type c2 = Type::getClass("Object", "apryx/lang");
		Type c3 = Type::getClass("String", "apryx/lang");

		assert(c1 == c1);
		assert(!(c2 == c3));

		LOG("Test done!");
	}

	void testDecoratedAST()
	{
		LOG("AST test start...");

		ApryxNamespace global;

		assert(global.addField("someField", Type::getInt()));
		assert(global.addField("otherField", Type::getFloat()));

		auto out = global.getFieldType("someField");
		assert(out);
		assert(out == Type::getInt());

		out = global.getFieldType("otherField");
		assert(out);
		assert(out == Type::getFloat());

		assert(global.validate());

		ApryxFunction function(Type::getVoid(), {
			{ "hi", Type::getInt() },
			{ "pizza", Type::getFloat() }
		});

		assert(function.getArgumentCount() == 2);

		assert(function.getReturnType() == Type::getVoid());
		assert(function.getArgumentType(0) == Type::getInt());
		assert(function.getArgumentType(1) == Type::getFloat());

		assert(function.getArgumentName(0) == "hi");
		assert(function.getArgumentName(1) == "pizza");

		assert(function.getArgumentByName("hi") == 0);
		assert(function.getArgumentByName("pizza") == 1);

		assert(function.validate());

		LOG("Test done!");
	}
}
