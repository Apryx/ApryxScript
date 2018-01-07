#include "ByteReader.h"

#include <sstream>

namespace apryx {

	ByteReader::ByteReader(ByteSequence bytes)
		: m_Sequence(bytes), m_Index(0)
	{

	}

	ByteCode ByteReader::readCode()
	{
		return (ByteCode) readUByte();
	}

	std::string ByteReader::readString()
	{
		std::stringstream stream;

		size_t length = readUShort();

		for (int i = 0; i < length; i++)
		{
			stream << (char)readUByte();
		}
	}

	uint8_t ByteReader::readUByte()
	{
		uint8_t v = m_Sequence[m_Index];
		
		m_Index++;

		return v;
	}

	uint16_t ByteReader::readUShort()
	{
		uint32_t b = readUByte();
		uint32_t a = readUByte();

		return (b << 8) | a;
	}

	uint32_t ByteReader::readUInt()
	{
		uint32_t d = readUByte();
		uint32_t c = readUByte();
		uint32_t b = readUByte();
		uint32_t a = readUByte();

		return  (d << 24) | (c << 16) | (b << 8) | a;
	}

	int8_t ByteReader::readByte()
	{
		uint8_t v = readUByte();

		int8_t *p = reinterpret_cast<int8_t*>(&v);

		return *p;
	}

	int16_t ByteReader::readShort()
	{
		uint32_t b = readUByte();
		uint32_t a = readUByte();

		return (b << 8) | a;
	}

	int32_t ByteReader::readInt()
	{
		uint32_t d = readUByte();
		uint32_t c = readUByte();
		uint32_t b = readUByte();
		uint32_t a = readUByte();

		return  (d << 24) | (c << 16) | (b << 8) | a;
	}

	bool ByteReader::done()
	{
		return m_Index >= m_Sequence.size();
	}
}
