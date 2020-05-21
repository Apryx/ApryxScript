#include "NameAndType.h"

#include <sstream>

namespace apryx {
	std::string apryx::NameAndType::toString()
	{
		std::stringstream stream;

		stream << m_Name;

		if (m_Type) {
			stream << " : " << m_Type->toString();
		}

		return stream.str();
	}
}
