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

		return stream.str();
	}

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
}
