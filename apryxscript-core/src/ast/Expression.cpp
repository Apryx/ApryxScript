#include "Expression.h"
#include <sstream>

#define DEBUG_EXTRA

namespace apryx {

	std::string OperatorExpression::toString()
	{
		std::stringstream stream;

		stream << "(";
		stream << m_Lhs->toString();
		stream << m_Operator;
		stream << m_Rhs->toString();
		stream << ")";

		return stream.str();
	}
	std::string IdentiefierExpression::toString()
	{
		return m_Identifier;
	}

	std::string InvokeExpression::toString()
	{

		std::stringstream stream;

		stream << "(";
		stream << m_Lhs->toString();
		stream << "(";
		stream << (m_Args == nullptr ? "" : m_Args->toString());
		stream << ")";
		stream << ")";

		return stream.str();
	}
	std::string ConstantExpression::toString()
	{
		if (m_Type == STRING) {
			return "\"" + m_Constant + "\"";
		}
		else {
			return m_Constant;
		}
	}
	std::string LookupExpression::toString()
	{
		std::stringstream stream;

		stream << "(";
		stream << m_Lhs->toString();
		stream << ".";
		stream << m_Rhs->toString();
		stream << ")";

		return stream.str();
	}
	std::string PrefixOperatorExpression::toString()
	{
		std::stringstream stream;

		stream << "(";
		stream << m_Operator;
		stream << m_Rhs->toString();
		stream << ")";

		return stream.str();
	}
}