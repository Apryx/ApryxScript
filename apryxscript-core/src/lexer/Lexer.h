#pragma once

#include "Characters.h"

namespace apryx {

	struct Token {

		enum Type {
			IDENTIFIER,
			KEYWORD, 

			STRING,
			INTEGER,
			LONG,
			FLOAT,
			DOUBLE,

			LINE_END,			// ;
			COLON,				// :
			
			OPEN_BRACKET,		// (
			CLOSE_BRACKET,		// )
			OPEN_CURLY,			// {
			CLOSE_CURLY,		// }

			OPERATOR_ADD,		// +
			OPERATOR_SUBTRACT,	// -
			OPERATOR_DIVIDE,	// /
			OPERATOR_MULTIPLY,	// *
			OPERATOR_LOOKUP,	// .
			OPERATOR_EQUALS,	// =

			SEPERATOR,			// ,

			END,				// FILE_END
			ERROR,				// Error
			UNKNOWN				// Unknown type
		};

		Type m_Type = Type::UNKNOWN;
		std::string m_Data;

		int m_Line;
		int m_Character;

		friend std::ostream &operator<<(std::ostream &o, const Token &token);
		friend std::ostream &operator<<(std::ostream &o, const Type &token);

		friend bool isOperator(const Token &token);

		operator bool() const;
	};

	class Lexer {
		Characters m_Chars;
		Token m_Current;

	public:
		Lexer(std::shared_ptr<std::istream> input);

		const Token &current();
		const Token &next();

		operator bool();
	private:
		const void unexpectedCharacter();
	};


}