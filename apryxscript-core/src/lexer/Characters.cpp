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
		if (m_Current == '\n'){
			m_Line++;
			m_Index = 0;
		}

		m_Input->get(m_Current);
		
		m_Index++;

		if (!this->operator bool())
			m_Current = '\0';


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
