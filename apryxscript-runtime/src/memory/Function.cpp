#include "Function.h"

#include <sstream>

namespace apryx{
	Function::Function(std::string name, Type returnType, std::vector<Field> parameters, ByteSequence code)
		:m_Name(name), m_ReturnType(returnType), m_Parameters(parameters), m_Code(code)
	{ }

	std::string Function::signature() const
	{
		std::stringstream string;

		string << m_Name;

		string << "(";

		for (int i = 0; i < m_Parameters.size(); i++) {
			string << m_Parameters[i].type().getTypeName();
		}

		string << (")");

		return string.str();
	}
}
