#pragma once

#include <string>

namespace apryx {
	bool isWhitespace(char c);
	bool isCharacter(char c);
	bool isNumber(char c);

	bool isKeyword(const std::string &str);
}