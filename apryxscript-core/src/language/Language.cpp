#include "Language.h"
#include <cctype>

namespace apryx {

	bool isWhitespace(char c)
	{
		return std::isspace(c);
	}

	bool isCharacter(char c)
	{
		return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
	}

	bool isNumber(char c)
	{
		return c >= '0' && c <= '9';
	}
	bool isKeyword(const std::string & str)
	{
		return
			str == "var" ||
			str == "function" ||
			str == "class" ||
			str == "struct" ||
			str == "init";
	}
	bool isOperator(const std::string & str)
	{
		//Maybe i can do my casting here too?
		return
			str == "new" ||
			str == "in";
	}
}
