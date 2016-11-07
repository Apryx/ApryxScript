#include "Lexer.h"
#include "language/Language.h"

#include <sstream>
#include <iostream>
#include <vector>
#include "logger/log.h"

#define LEXER_ERROR(x) throw std::exception(x)

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
		m_Current.m_Line = m_Chars.line();
		m_Current.m_Character = m_Chars.index();
		
		//End of stream
		if (!m_Chars.current()) {
			m_Current.m_Type = Token::END;
			return m_Current;
		}
		char c = m_Chars.current();

		//-------------------------------------------------------------------------------------//
		// Identifiers, keywords and operator keywords
		//-------------------------------------------------------------------------------------//
		if (isCharacter(c) || c == '_') {
			std::stringstream stream;

			if (c == '_') {
				LOG_WARNING("Warning! Names starting with '_' reserved for compiler names. Attempting to continue, but may result in unexpected behaviour!");
			}
			
			while ((isCharacter(c) || isNumber(c) || c == '_') && m_Chars) {
				stream << c;
				
				c = m_Chars.next();
			}

			m_Current.m_Data = stream.str();

			if (getKeywordType(m_Current.m_Data) != Token::ERROR)
				m_Current.m_Type = getKeywordType(m_Current.m_Data);
			else
				m_Current.m_Type = Token::IDENTIFIER;

			return m_Current;
		}

		//-------------------------------------------------------------------------------------//
		// Whitespace
		//-------------------------------------------------------------------------------------//
		else if (isWhitespace(c)) {
			//Consume the whitespace
			m_Chars.next();
			//Return the next token
			return next();
		}

		//-------------------------------------------------------------------------------------//
		// Numbers
		//-------------------------------------------------------------------------------------//

		else if (isNumber(c)) {

			std::stringstream stream;
			while (isNumber(c) && m_Chars) {
				stream << c;

				c = m_Chars.next();
			}

			//Dot number
			if (c == '.' && m_Chars) {
				stream << '.';
				c = m_Chars.next();
				while (isNumber(c) && m_Chars) {
					stream << c;

					c = m_Chars.next();
				}

				if (c == 'd' || isWhitespace(c) || !isCharacter(c)) {
					if (c == 'd')
						m_Chars.next();
					m_Current.m_Data = stream.str();
					m_Current.m_Type = Token::DOUBLE;
					return m_Current;
				}
				else if (c == 'f') {
					m_Chars.next();
					m_Current.m_Data = stream.str();
					m_Current.m_Type = Token::FLOAT;
					return m_Current;
				}
				else{
					unexpectedCharacter();
				}
			}
			//Its a long
			else if(c == 'l'){
				m_Chars.next();
				
				m_Current.m_Data = stream.str();
				m_Current.m_Type = Token::LONG;
				return m_Current;
			}
			else if (c == 'f') {
				m_Chars.next();

				m_Current.m_Data = stream.str();
				m_Current.m_Type = Token::FLOAT;
				return m_Current;
			}
			else if (c == 'd') {
				m_Chars.next();

				m_Current.m_Data = stream.str();
				m_Current.m_Type = Token::DOUBLE;
				return m_Current;
			}
			else if(isCharacter(c)){
				unexpectedCharacter();
			}
			else {
				m_Current.m_Data = stream.str();
				m_Current.m_Type = Token::INTEGER;
				return m_Current;
			}
			
			assert(false);
		}

		//-------------------------------------------------------------------------------------//
		// String literals
		//-------------------------------------------------------------------------------------//
		else if (c == '"') {
			std::stringstream stream;

			c = m_Chars.next();
			while (c != '"' && m_Chars) {
				stream << c;
				c = m_Chars.next();
			}

			//consume the last "
			m_Chars.next();

			m_Current.m_Data = stream.str();
			m_Current.m_Type = Token::STRING;

			return m_Current;
		}


		//-------------------------------------------------------------------------------------//
		// Brackets
		//-------------------------------------------------------------------------------------//
		else if (c == '{') {
			m_Current.m_Data = "{";
			m_Current.m_Type = Token::OPEN_CURLY;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '}') {
			m_Current.m_Data = "}";
			m_Current.m_Type = Token::CLOSE_CURLY;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '(') {
			m_Current.m_Data = "(";
			m_Current.m_Type = Token::OPEN_BRACKET;
			m_Chars.next();
			return m_Current;
		}
		else if (c == ')') {
			m_Current.m_Data = ")";
			m_Current.m_Type = Token::CLOSE_BRACKET;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '[') {
			m_Current.m_Data = "[";
			m_Current.m_Type = Token::OPEN_SQUARE;
			m_Chars.next();
			return m_Current;
		}
		else if (c == ']') {
			m_Current.m_Data = "]";
			m_Current.m_Type = Token::CLOSE_SQUARE;
			m_Chars.next();
			return m_Current;
		}

		//-------------------------------------------------------------------------------------//
		// Simple operators
		//-------------------------------------------------------------------------------------//
		else if (c == '.') {
			m_Current.m_Data = ".";
			m_Current.m_Type = Token::OPERATOR_LOOKUP;
			m_Chars.next();
			return m_Current;
		}
		else if (c == ',') {
			m_Current.m_Data = ",";
			m_Current.m_Type = Token::SEPERATOR;
			m_Chars.next();
			return m_Current;
		}
		else if (c == ':') {
			c = m_Chars.next();
			if (c == ':') {
				m_Current.m_Data = "::";
				m_Current.m_Type = Token::OPERATOR_SCOPE;
				m_Chars.next();
			}
			else {
				m_Current.m_Data = ":";
				m_Current.m_Type = Token::COLON;
			}
			return m_Current;
		}
		else if (c == ';') {
			m_Current.m_Data = ";";
			m_Current.m_Type = Token::LINE_END;
			m_Chars.next();
			return m_Current;
		}
		//-------------------------------------------------------------------------------------//
		//Operators and assignment
		//-------------------------------------------------------------------------------------//
		else if (c == '=') {
			m_Current.m_Data = "=";
			m_Current.m_Type = Token::OPERATOR_EQUALS;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "==";
				m_Current.m_Type = Token::OPERATOR_CMP_EQ;
			}
			return m_Current;
		}
		else if (c == '+') {
			m_Current.m_Data = "+";
			m_Current.m_Type = Token::OPERATOR_ADD;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "+=";
				m_Current.m_Type = Token::OPERATOR_ADD_EQ;
			}
			return m_Current;
		}
		else if (c == '-') {
			m_Current.m_Data = "-";
			m_Current.m_Type = Token::OPERATOR_SUBTRACT;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "-=";
				m_Current.m_Type = Token::OPERATOR_SUB_EQ;
			}
			return m_Current;
		}
		else if (c == '*') {
			m_Current.m_Data = "*";
			m_Current.m_Type = Token::OPERATOR_MULTIPLY;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "*=";
				m_Current.m_Type = Token::OPERATOR_MUL_EQ;
			}
			return m_Current;
		}
		else if (c == '/') {
			m_Current.m_Data = "/";
			m_Current.m_Type = Token::OPERATOR_DIVIDE;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "/=";
				m_Current.m_Type = Token::OPERATOR_DIV_EQ;
			}

			//One line comment
			else if (c == '/') {
				//Look for newline
				while (c != '\n' && m_Chars) {
					c = m_Chars.next();
				}
				return next();
			}

			//Mutli line comment
			else if (c == '*') {
				//Look for newline
				while (m_Chars) {
					c = m_Chars.next();
					if (c == '*') {
						c = m_Chars.next();
						if (c == '/') {
							m_Chars.next();
							break;
						}
					}
				}
				return next();
			}

			return m_Current;
		}
		else if (c == '%') {
			m_Current.m_Data = "%";
			m_Current.m_Type = Token::OPERATOR_MOD;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "%=";
				m_Current.m_Type = Token::OPERATOR_MOD_EQ;
			}
			return m_Current;
		}
		//-------------------------------------------------------------------------------------//
		//Bitwise and logic operators
		//-------------------------------------------------------------------------------------//
		else if (c == '~') {
			m_Current.m_Data = "~";
			m_Current.m_Type = Token::OPERATOR_BIT_INV;
			c = m_Chars.next();
			return m_Current;
		}
		else if (c == '^') {
			m_Current.m_Data = "^";
			m_Current.m_Type = Token::OPERATOR_BIT_XOR;
			c = m_Chars.next();
			return m_Current;
		}
		else if (c == '|') {
			m_Current.m_Data = "|";
			m_Current.m_Type = Token::OPERATOR_BIT_OR;
			c = m_Chars.next();
			if (c == '|') {
				m_Chars.next();
				m_Current.m_Data = "||";
				m_Current.m_Type = Token::OPERATOR_LOGIC_OR;
			}
			return m_Current;
		}
		else if (c == '&') {
			m_Current.m_Data = "&";
			m_Current.m_Type = Token::OPERATOR_BIT_AND;
			c = m_Chars.next();
			if (c == '&') {
				m_Chars.next();
				m_Current.m_Data = "&&";
				m_Current.m_Type = Token::OPERATOR_LOGIC_AND;
			}
			return m_Current;
		}
		else if (c == '<') {
			m_Current.m_Data = "<";
			m_Current.m_Type = Token::OPERATOR_CMP_LT;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "<=";
				m_Current.m_Type = Token::OPERATOR_CMP_LTEQ;
			}
			else if (c == '<') {
				m_Chars.next();
				m_Current.m_Data = "<<";
				m_Current.m_Type = Token::OPERATOR_BIT_SL;
			}
			return m_Current;
		}
		else if (c == '>') {
			m_Current.m_Data = ">";
			m_Current.m_Type = Token::OPERATOR_CMP_GT;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = ">=";
				m_Current.m_Type = Token::OPERATOR_CMP_GTEQ;
			}
			else if (c == '>') {
				m_Chars.next();
				m_Current.m_Data = ">>";
				m_Current.m_Type = Token::OPERATOR_BIT_SR;
			}
			return m_Current;
		}
		else if (c == '!') {
			m_Current.m_Data = "!";
			m_Current.m_Type = Token::OPERATOR_NOT;
			c = m_Chars.next();
			if (c == '=') {
				m_Chars.next();
				m_Current.m_Data = "!=";
				m_Current.m_Type = Token::OPERATOR_CMP_NEQ;
			}
			return m_Current;
		}

		else {
			unexpectedCharacter();
			m_Chars.next();
			return next();
		}

		//Shouldn't be reached
		assert(false);

		return m_Current;
	}

	Lexer::operator bool()
	{
		return m_Chars;
	}

	const void Lexer::unexpectedCharacter()
	{
		LOG_ERROR("Unexpected character at line " << m_Chars.line() << " (" << m_Chars.index() << ") : " << m_Chars.current());
	}

	std::ostream & operator<<(std::ostream & o, const Token & t)
	{

		return o << "(" << t.m_Type << " - " << t.m_Line << ":" << t.m_Character << ") " << t.m_Data;
	}

	std::ostream & operator<<(std::ostream & o, const Token::Type & token)
	{
		switch (token) {
		case Token::IDENTIFIER:
			o << "IDENTIFIER";
			break;
		case Token::KEYWORD_CLASS:
			o << "KEYWORD_CLASS";
			break;
		case Token::KEYWORD_STRUCT:
			o << "KEYWORD_STRUCT";
			break;
		case Token::KEYWORD_FUNCTION:
			o << "KEYWORD_FUNCTION";
			break;
		case Token::KEYWORD_VARIABLE:
			o << "KEYWORD_VARIABLE";
			break;

		case Token::MODIFIER_PUBLIC:
			o << "MODIFIER_PUBLIC";
			break;
		case Token::MODIFIER_PROTECTED:
			o << "MODIFIER_PROTECTED";
			break;
		case Token::MODIFIER_PRIVATE:
			o << "MODIFIER_PRIVATE";
			break;
		case Token::MODIFIER_STATIC:
			o << "MODIFIER_STATIC";
			break;

		case Token::KEYWORD_IN:
			o << "OPERATOR_KEYWORD";
			break;
		case Token::KEYWORD_RETURN:
			o << "KEYWORD_RETURN";
			break;

		case Token::KEYWORD_IF:
			o << "OPERATOR_KEYWORD";
			break;
		case Token::KEYWORD_ELSE:
			o << "KEYWORD_ELSE";
			break;
		case Token::KEYWORD_FOR:
			o << "KEYWORD_FOR";
			break;
		case Token::KEYWORD_WHILE:
			o << "KEYWORD_WHILE";
			break;
		case Token::KEYWORD_REPEAT:
			o << "KEYWORD_REPEAT";
			break;
		case Token::KEYWORD_EXTENDS:
			o << "KEYWORD_EXTENDS";
			break;

		case Token::STRING:
			o << "STRING";
			break;
		case Token::INTEGER:
			o << "INTEGER";
			break;
		case Token::LONG:
			o << "LONG";
			break;
		case Token::FLOAT:
			o << "FLOAT";
			break;
		case Token::DOUBLE:
			o << "DOUBLE";
			break;

		case Token::LINE_END:
			o << "LINE_END";
			break;
		case Token::COLON:
			o << "COLON";
			break;

		case Token::OPEN_BRACKET:
			o << "OPEN_BRACKET";
			break;
		case Token::CLOSE_BRACKET:
			o << "CLOSE_BRACKET";
			break;
		case Token::OPEN_CURLY:
			o << "OPEN_CURLY";
			break;
		case Token::CLOSE_CURLY:
			o << "CLOSE_CURLY";
			break;
		case Token::OPEN_SQUARE:
			o << "OPEN_SQUARE";
			break;
		case Token::CLOSE_SQUARE:
			o << "CLOSE_SQUARE";
			break;

		case Token::OPERATOR_NEW:
			o << "OPERATOR_NEW";
			break;

		case Token::OPERATOR_ADD:
			o << "OPERATOR_ADD";
			break;
		case Token::OPERATOR_SUBTRACT:
			o << "OPERATOR_SUBTRACT";
			break;
		case Token::OPERATOR_DIVIDE:
			o << "OPERATOR_DIVIDE";
			break;
		case Token::OPERATOR_MULTIPLY:
			o << "OPERATOR_MULTIPLY";
			break;
		case Token::OPERATOR_MOD:
			o << "OPERATOR_MOD";
			break;
		case Token::OPERATOR_LOOKUP:
			o << "OPERATOR_LOOKUP";
			break;
		case Token::OPERATOR_EQUALS:
			o << "OPERATOR_EQUALS";
			break;
		case Token::OPERATOR_SCOPE:
			o << "OPERATOR_SCOPE";
			break;
		case Token::OPERATOR_NOT:
			o << "OPERATOR_NOT";
			break;
		case Token::OPERATOR_CMP_GT:
			o << "OPERATOR_CMP_GT";
			break;
		case Token::OPERATOR_CMP_LT:
			o << "OPERATOR_CMP_LT";
			break;
		case Token::OPERATOR_CMP_GTEQ:
			o << "OPERATOR_CMP_GTEQ";
			break;
		case Token::OPERATOR_CMP_LTEQ:
			o << "OPERATOR_CMP_LTEQ";
			break;
		case Token::OPERATOR_CMP_EQ:
			o << "OPERATOR_CMP_EQ";
			break;
		case Token::OPERATOR_CMP_NEQ:
			o << "OPERATOR_CMP_NEQ";
			break;
		case Token::OPERATOR_ADD_EQ:
			o << "OPERATOR_ADD_EQ";
			break;
		case Token::OPERATOR_SUB_EQ:
			o << "OPERATOR_SUB_EQ";
			break;
		case Token::OPERATOR_MUL_EQ:
			o << "OPERATOR_MUL_EQ";
			break;
		case Token::OPERATOR_DIV_EQ:
			o << "OPERATOR_DIV_EQ";
			break;
		case Token::OPERATOR_MOD_EQ:
			o << "OPERATOR_MOD_EQ";
			break;

		case Token::OPERATOR_LOGIC_AND:
			o << "OPERATOR_LOGIC_AND";
			break;
		case Token::OPERATOR_LOGIC_OR:
			o << "OPERATOR_LOGIC_OR";
			break;

		case Token::OPERATOR_BIT_SR:
			o << "OPERATOR_BIT_SR";
			break;
		case Token::OPERATOR_BIT_SL:
			o << "OPERATOR_BIT_SL";
			break;
		case Token::OPERATOR_BIT_INV:
			o << "OPERATOR_BIT_INV";
			break;
		case Token::OPERATOR_BIT_XOR:
			o << "OPERATOR_BIT_XOR";
			break;
		case Token::OPERATOR_BIT_OR:
			o << "OPERATOR_BIT_OR";
			break;
		case Token::OPERATOR_BIT_AND:
			o << "OPERATOR_BIT_AND";
			break;

		case Token::SEPERATOR:
			o << "SEPERATOR";
			break;
		case Token::END:
			o << "END";
			break;
		case Token::ERROR:
			o << "ERROR";
			break;
		case Token::UNKNOWN:
			o << "UNKNOWN";
			break;
		default:
			o << "Unimplmented";
			break;
		}
		return o;
	}

	const std::vector<Token::Type> valueTypes = {
		Token::Type::IDENTIFIER,

		Token::Type::STRING,
		Token::Type::INTEGER,
		Token::Type::LONG,
		Token::Type::FLOAT,
		Token::Type::DOUBLE,
	};

	const std::vector<std::pair<Token::Type, std::string>> keywordTypes = {
		{ Token::Type::KEYWORD_CLASS, "class" },
		{ Token::Type::KEYWORD_FUNCTION, "function" },
		{ Token::Type::KEYWORD_STRUCT, "struct" },
		{ Token::Type::KEYWORD_VARIABLE, "var" },

		{ Token::Type::KEYWORD_FOR, "for" },
		{ Token::Type::KEYWORD_REPEAT, "repeat" },
		{ Token::Type::KEYWORD_WHILE, "while" },
		{ Token::Type::KEYWORD_IF, "if" },
		{ Token::Type::KEYWORD_ELSE, "else" },

		{ Token::Type::KEYWORD_IN, "in" },
		{ Token::Type::KEYWORD_RETURN, "return" },

		{ Token::Type::KEYWORD_EXTENDS, "extends" },
	};

	const std::vector<std::pair<Token::Type, std::string>> modifierTypes = {
		{ Token::Type::MODIFIER_PUBLIC, "public" },
		{ Token::Type::MODIFIER_PROTECTED, "protected" },
		{ Token::Type::MODIFIER_PRIVATE, "private" },
		{ Token::Type::MODIFIER_STATIC, "static" },
		{ Token::Type::MODIFIER_LOCAL, "local" },
	};

	const std::vector<std::pair<Token::Type, std::string>> keywordOperatorTypes = {
		{ Token::Type::OPERATOR_NEW, "new" },
	};

	const std::vector<Token::Type> operatorTypes = {
		Token::Type::OPERATOR_ADD,		// +
		Token::Type::OPERATOR_SUBTRACT,	// -
		Token::Type::OPERATOR_DIVIDE,	// /
		Token::Type::OPERATOR_MULTIPLY,	// *
		Token::Type::OPERATOR_MOD,		// %

		Token::Type::OPERATOR_BIT_SR,	// >>
		Token::Type::OPERATOR_BIT_SL,	// <<
		Token::Type::OPERATOR_BIT_INV,	// ~
		Token::Type::OPERATOR_BIT_XOR,	// ^
		Token::Type::OPERATOR_BIT_OR,	// |
		Token::Type::OPERATOR_BIT_AND,	// &

		Token::Type::OPERATOR_LOOKUP,	// .
		Token::Type::OPERATOR_NOT,		// !

		Token::Type::OPERATOR_CMP_GT,	// >
		Token::Type::OPERATOR_CMP_LT,	// <
		Token::Type::OPERATOR_CMP_GTEQ,	// >=
		Token::Type::OPERATOR_CMP_LTEQ,	// <=
		Token::Type::OPERATOR_CMP_EQ,	// ==
		Token::Type::OPERATOR_CMP_NEQ,	// !=

		Token::Type::OPERATOR_LOGIC_AND,	// &&
		Token::Type::OPERATOR_LOGIC_OR,	// ||

		Token::Type::OPERATOR_EQUALS,	// =
		Token::Type::OPERATOR_ADD_EQ,	// +=
		Token::Type::OPERATOR_SUB_EQ,	// -=
		Token::Type::OPERATOR_MUL_EQ,	// *=
		Token::Type::OPERATOR_DIV_EQ,	// /=
		Token::Type::OPERATOR_MOD_EQ,	// %=

		Token::Type::OPERATOR_SCOPE,		// ::

		Token::Type::SEPERATOR			// ,
	};

	bool isOperator(const Token & token)
	{
		auto t = token.m_Type;
		
		for (auto s : operatorTypes)
		{
			if (s == t)
				return true;
		}

		return false;
	}

	bool isValueType(const Token & token)
	{
		auto t = token.m_Type;

		for (auto s : valueTypes)
		{
			if (s == t)
				return true;
		}

		return false;
	}

	bool isKeyword(const Token & token)
	{
		auto t = token.m_Type;

		for (auto s : keywordTypes)
		{
			if (s.first == t)
				return true;
		}

		return false;
	}

	Token::Type getKeywordType(const std::string & name)
	{
		for (auto s : keywordTypes)
		{
			if (s.second == name)
				return s.first;
		}
		for (auto s : modifierTypes)
		{
			if (s.second == name)
				return s.first;
		}
		for (auto s : keywordOperatorTypes)
		{
			if (s.second == name)
				return s.first;
		}

		return Token::ERROR;
	}

	bool isModifier(const Token & token)
	{
		auto t = token.m_Type;

		for (auto s : modifierTypes)
		{
			if (s.first == t)
				return true;
		}

		return false;
	}

	Token::operator bool() const
	{
		return m_Type != END && m_Type != UNKNOWN;
	}
}
