#include "Lexer.h"
#include "language/Language.h"

namespace apryx {
	Lexer::Lexer(std::shared_ptr<std::istream> input)
		:m_Chars(input)
	{

	}
	const Token & Lexer::current()
	{
		return m_Current;
	}

	const Token & Lexer::next()
	{

	}
}
