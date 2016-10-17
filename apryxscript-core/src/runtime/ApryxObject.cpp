#include "ApryxObject.h"
#include <sstream>

namespace apryx {

	std::string ApryxObject::toString()
	{
		return m_Data;
	}

	void apryx::ApryxObject::assign(const ApryxObject & value)
	{
		this->m_Data = value.m_Data;
	}

	bool toFloat(const std::string & string, float & f)
	{
		std::istringstream stream(string);
		stream >> f;
		return stream.eof() && !stream.fail();
	}
	std::string toString(float f)
	{
		std::stringstream stream;

		stream << f;

		return stream.str();
	}
}
