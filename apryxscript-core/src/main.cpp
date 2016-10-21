//TODO move this to different project (apryxscript-application)

#include "debug/Debug.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Statement.h"
#include "runtime/Runtime.h"

#include <memory>
#include <fstream>
#include <sstream>


int main(void)
{
	using namespace apryx;

	//Lexer lexer(std::make_shared<std::ifstream>("test.apx"));
	Parser parser;
	Runtime runtime;

	while (true) {
		std::string line;
		std::cout << ">";
		getline(std::cin, line);

		Lexer lexer(std::make_shared<std::stringstream>(line));
		lexer.next();

		while (lexer.current()) {
			auto p = parser.parseStatement(lexer);
			if (p) {
				LOG(p->toString());
			}
		}

	}
	WAIT();

	return 0;
}