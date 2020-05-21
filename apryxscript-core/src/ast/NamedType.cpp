#include "NamedType.h"

#include <sstream>

namespace apryx {
	
	std::string apryx::NamedType::toString()
	{
		std::stringstream stream;

		stream << m_Name;

		return stream.str();
	}
}