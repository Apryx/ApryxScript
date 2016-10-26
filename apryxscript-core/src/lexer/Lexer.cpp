#include "Lexer.h"
#include "language/Language.h"

#include <sstream>
#include <iostream>
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

		//Multicharacter stuff
		if (isCharacter(c)) {
			std::stringstream stream;
			
			while ((isCharacter(c) || isNumber(c)) && m_Chars) {
				stream << c;
				
				c = m_Chars.next();
			}

			m_Current.m_Data = stream.str();
			if (isKeyword(m_Current.m_Data))
				m_Current.m_Type = Token::KEYWORD;
			else
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

		//Operators TODO

		//Single character token
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
			m_Current.m_Data = ":";
			m_Current.m_Type = Token::COLON;
			m_Chars.next();
			return m_Current;
		}
		else if (c == ';') {
			m_Current.m_Data = ";";
			m_Current.m_Type = Token::LINE_END;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '=') {
			m_Current.m_Data = "=";
			m_Current.m_Type = Token::OPERATOR_EQUALS;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '+') {
			m_Current.m_Data = "+";
			m_Current.m_Type = Token::OPERATOR_ADD;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '-') {
			m_Current.m_Data = "-";
			m_Current.m_Type = Token::OPERATOR_SUBTRACT;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '*') {
			m_Current.m_Data = "*";
			m_Current.m_Type = Token::OPERATOR_MULTIPLY;
			m_Chars.next();
			return m_Current;
		}
		else if (c == '/') {
			m_Current.m_Data = "/";
			m_Current.m_Type = Token::OPERATOR_DIVIDE;
			m_Chars.next();
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
		case Token::KEYWORD:
			o << "KEYWORD";
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
		case Token::OPERATOR_LOOKUP:
			o << "OPERATOR_LOOKUP";
			break;
		case Token::OPERATOR_EQUALS:
			o << "OPERATOR_EQUALS";
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

	bool isOperator(const Token & token)
	{
		auto t = token.m_Type;
		return
			t == Token::OPERATOR_ADD ||
			t == Token::OPERATOR_SUBTRACT ||
			t == Token::OPERATOR_DIVIDE ||
			t == Token::OPERATOR_MULTIPLY ||
			t == Token::OPERATOR_EQUALS;
	}

	Token::operator bool() const
	{
		return m_Type != END && m_Type != UNKNOWN;
	}
}
