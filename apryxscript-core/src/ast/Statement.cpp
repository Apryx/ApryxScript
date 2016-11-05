#include "Statement.h"
#include "Expression.h"
#include <sstream>

#include "vm/VMWriter.h"

namespace apryx {
	std::string Variable::toString()
	{
		std::stringstream stream;

		stream << "var ";
		stream << m_Name;
		if (m_Type.size() > 0)
			stream << ":" << m_Type;
		if (m_InitialValue)
			stream << "=" << m_InitialValue->toString();

		stream << ";";

		return stream.str();
	}

	
	std::string Block::toString()
	{
		std::stringstream stream;

		stream << "{";
		for (auto &a : m_Statements)
			stream << a->toString();
		stream << "}";

		return stream.str();
	}
	std::string ReturnStatement::toString()
	{
		std::stringstream stream;

		stream << "return ";
		stream << m_ReturnExpression->toString();
		stream << ";";

		return stream.str();
	}
	std::string Function::toString()
	{
		std::stringstream stream;

		stream << "function ";
		stream << m_Name;
		stream << "(" << (m_Arguments ? m_Arguments->toString() : "") << ")";
		stream << ":";
		stream << m_ReturnType;
		stream << m_Statement->toString();

		return stream.str();
	}
	std::string ExpressionStatement::toString()
	{
		std::stringstream stream;

		stream << m_Expression->toString();
		stream << ";";

		return stream.str();
	}

	//LEGACY
	std::string Context::toString()
	{
		return std::string();
	}

	void Context::performOperator(VMWriter &vmw, const std::string & op)
	{
		if (op == "+") {
			vmw.fadd();
		}
		else if (op == "-") {
			vmw.fsub();
		}
		else if (op == "*") {
			vmw.fmul();
		}
		else if (op == "/") {
			vmw.fdiv();
		}
	}

	void Context::performPrefixOperator(VMWriter &vmw, const std::string & op)
	{

	}
	std::string Structure::toString()
	{
		std::stringstream stream;

		stream << "class ";
		stream << m_Name;
		stream << " extends ";
		stream << m_Parent;
		stream << m_Statement->toString();

		return stream.str();
	}
}
