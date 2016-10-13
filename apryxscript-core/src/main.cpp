//TODO move this to different project (apryxscript-application)

#include "debug/Debug.h"
#include "lexer/Lexer.h"

#include <memory>
#include <fstream>

int main(void)
{
	using namespace apryx;

	Lexer lexer(std::make_shared<std::ifstream>("test.apx"));



	WAIT();

	return 0;
}