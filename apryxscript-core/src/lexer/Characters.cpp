#include "Characters.h"

namespace apryx {

	Characters::Characters(std::shared_ptr<std::istream> input)
		:m_Input(input), m_Current('\0')
	{
	}

	char Characters::current()
	{
		return m_Current;
	}

	char Characters::next()
	{
		m_Input->get(m_Current);
		if (this->operator bool())
			return m_Current;
		else
			return '\0';
	}

	Characters::operator bool()
	{
		return m_Input.operator bool() && m_Input->operator bool();
	}

	bool Characters::operator!()
	{
		return !this->operator bool();
	}
}
