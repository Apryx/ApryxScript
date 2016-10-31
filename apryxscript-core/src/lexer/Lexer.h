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
			OPEN_SQUARE,		// [
			CLOSE_SQUARE,		// ]

			//These should have their own thingy
			OPERATOR_KEYWORD,	// new in

			OPERATOR_ADD,		// +
			OPERATOR_SUBTRACT,	// -
			OPERATOR_DIVIDE,	// /
			OPERATOR_MULTIPLY,	// *
			OPERATOR_MOD,		// %

			OPERATOR_BIT_SR,	// >>
			OPERATOR_BIT_SL,	// <<
			OPERATOR_BIT_INV,	// ~
			OPERATOR_BIT_XOR,	// ^
			OPERATOR_BIT_OR,	// |
			OPERATOR_BIT_AND,	// &

			OPERATOR_LOOKUP,	// .
			OPERATOR_NOT,		// !

			OPERATOR_CMP_GT,	// >
			OPERATOR_CMP_LT,	// <
			OPERATOR_CMP_GTEQ,	// >=
			OPERATOR_CMP_LTEQ,	// <=
			OPERATOR_CMP_EQ,	// ==
			OPERATOR_CMP_NEQ,	// !=

			OPERATOR_LOGIC_AND,	// &&
			OPERATOR_LOGIC_OR,	// ||

			OPERATOR_EQUALS,	// =
			OPERATOR_ADD_EQ,	// +=
			OPERATOR_SUB_EQ,	// -=
			OPERATOR_MUL_EQ,	// *=
			OPERATOR_DIV_EQ,	// /=
			OPERATOR_MOD_EQ,	// %=

			OPERATOR_SCOPE,		// ::

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
		friend bool isValueType(const Token &token);

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