#pragma once

#include "bytecode/ByteCode.h"
#include <vector>

#include <string>

namespace apryx {

	class ByteReader {
		size_t m_Index;
		ByteSequence m_Sequence;
	public:
		ByteReader(ByteSequence bytes);

		ByteCode readCode();

		std::string readString();
		
		uint8_t readUByte();
		uint16_t readUShort();
		uint32_t readUInt();

		int8_t readByte();
		int16_t readShort();
		int32_t readInt();

		bool done();
	};

}