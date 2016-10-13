#pragma once

#include "Characters.h"

namespace apryx {

	class Lexer {
		Characters chars;
	public:
		Lexer(std::shared_ptr<std::istream> input);
	};

}