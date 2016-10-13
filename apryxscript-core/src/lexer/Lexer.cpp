#include "Lexer.h"
#include "language/Language.h"

#include <sstream>
#include <iostream>
#include "debug/Debug.h"

#define LEXER_ERROR(x) throw std::exception(x)
#define UNEXPECTED_CHARACTER(x) throw std::exception("Unexpected character at ");

namespace apryx {
	Lexer::Lexer(std::shared_ptr<std::istream> input)
		:m_Chars(input)
	{
		//Prepare the first thing
		m_Chars.next();
	}

	const Token & Lexer::current()
	{
		return m_Current;
	}

	const Token & Lexer::next()
	{
		if (!m_Chars.current())
			LEXER_ERROR("Lexer error, current == empty");

		char c = m_Chars.current();
		
		//Identifier
		if (isCharacter(c)) {
			std::stringstream stream;

			m_Current.m_Line = m_Chars.line();
			m_Current.m_Character = m_Chars.index();
			
			while (isCharacter(c) && m_Chars) {
				stream << c;
				
				c = m_Chars.next();
			}

			m_Current.m_Data = stream.str();
			m_Current.m_Type = Token::IDENTIFIER;

			return m_Current;
		}
		else if (isWhitespace(c)) {
			//Consume the whitespace
			m_Chars.next();
			//Return the next token
			return next();
		}
		else if (isNumber(c)) {
			m_Chars.next();
			return next();
		}
		else {
			m_Chars.next();
			return next();
		}

		//Shouldn't be reached
		assert(false);
	}

	Lexer::operator bool()
	{
		return m_Chars;
	}

	std::ostream & operator<<(std::ostream & o, const Token & t)
	{
		return o << "(" << t.m_Type << " - " << t.m_Line << ":" << t.m_Character << ")" << t.m_Data;
	}
}
