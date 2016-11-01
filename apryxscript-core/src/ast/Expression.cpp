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
	void OperatorExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
	}
	std::string IdentiefierExpression::toString()
	{
		return m_Identifier;
	}

	void IdentiefierExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
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
	void InvokeExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
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
	void ConstantExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
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
	void LookupExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
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
	void PrefixOperatorExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
	}
	std::string ListExpression::toString()
	{
		std::stringstream stream;
		
		for (int i = 0; i < m_List.size(); i++) {
			stream << m_List[i]->toString();

			if (i != m_List.size() - 1)
				stream << ",";
		}

		return stream.str();
	}
	void ListExpression::accept(ExpressionVisitor & exp)
	{
		exp.visit(*this);
	}
}