#include "ByteStack.h"

#include <iostream>

namespace apryx {

	void ByteStack::pushInt(int i)
	{
		uint8_t a = (uint8_t)(i);
		uint8_t b = (uint8_t)(i >> 8);
		uint8_t c = (uint8_t)(i >> 16);
		uint8_t d = (uint8_t)(i >> 24);

		m_Data.push_back(a);
		m_Data.push_back(b);
		m_Data.push_back(c);
		m_Data.push_back(d);
	}

	int ByteStack::popInt()
	{
		uint32_t d = popUByte();
		uint32_t c = popUByte();
		uint32_t b = popUByte();
		uint32_t a = popUByte();

		 return  (d << 24) | (c << 16) | (b << 8) | a;
	}

	bool ByteStack::empty()
	{
		return m_Data.empty();
	}

	size_t ByteStack::height()
	{
		return m_Data.size();
	}

	void ByteStack::pushUByte(uint8_t byte)
	{
		m_Data.push_back(byte);
	}

	uint8_t ByteStack::popUByte()
	{
		uint8_t last = m_Data.back();

		m_Data.pop_back();

		return last;
	}
}
