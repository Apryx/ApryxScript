#include "Expression.h"
#include <sstream>

namespace apryx {
	std::string OperatorExpression::toString()
	{
		return m_Lhs->toString() + m_Operator + m_Rhs->toString();
	}
	std::string IdentiefierExpression::toString()
	{
		return m_Identifier;
	}
	std::string ListExpression::toString()
	{
		std::stringstream stream;
		for (auto a : this->m_Expressions)
			stream << a->toString() << (a != m_Expressions.back() ? "," : "");
		return stream.str();
	}
	std::string InvokeExpression::toString()
	{
		return m_Lhs->toString()
			+ "("
			+ (m_Args == nullptr ? "" : m_Args->toString())
			+ ")";
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
}