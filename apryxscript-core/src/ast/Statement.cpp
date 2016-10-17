#include "Statement.h"
#include "Expression.h"
#include <sstream>

std::string apryx::Variable::toString()
{
	std::stringstream stream;

	stream << "var ";
	stream << m_Name;
	if (m_Type.size() > 0)
		stream << ":" <<  m_Type;
	if (m_InitialValue)
		stream << "=" << m_InitialValue->toString();

	return stream.str();
}
