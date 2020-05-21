#include "Expression.h"
#include <sstream>

#include "ASTVisitor.h"

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
	void OperatorExpression::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}
	std::string IdentiefierExpression::toString()
	{
		return m_Identifier;
	}

	void IdentiefierExpression::accept(ASTVisitor & exp)
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
	void InvokeExpression::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}
	std::string LiteralExpression::toString()
	{
		if (m_Type == LiteralExpression::STRING) {
			return "\"" + m_Value + "\"";
		}
		else {
			return m_Value;
		}
	}
	void LiteralExpression::accept(ASTVisitor & exp)
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
	void LookupExpression::accept(ASTVisitor & exp)
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
	void PrefixOperatorExpression::accept(ASTVisitor & exp)
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
	void ListExpression::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}


	
}