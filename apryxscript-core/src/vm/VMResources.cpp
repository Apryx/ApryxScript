#include "VMResources.h"
#include "VMValue.h"

namespace apryx {

	//==============================WRITE==============================//

	void VMResources::writeInstruction(std::vector<instruction_t>& target, instruction_t instruction)
	{
		target.push_back(instruction);
	}

	void VMResources::writeIndex(std::vector<instruction_t>& target, index_t i)
	{
		VMValue slot;
		slot.m_Index = i;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeFloat(std::vector<instruction_t>& target, float_t f)
	{
		VMValue slot;
		slot.m_Float = f;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeInt(std::vector<instruction_t>& target, int_t i)
	{
		VMValue slot;
		slot.m_Int = i;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeShort(std::vector<instruction_t>& target, short_t s)
	{
		VMValue slot;
		slot.m_Short = s;

		for (int i = 0; i < 2; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeByte(std::vector<instruction_t>& target, byte_t b)
	{
		writeInstruction(target, b);
	}

	void VMResources::writeFunction(std::vector<instruction_t>& target, native_t function)
	{
		VMValue slot;
		slot.m_Native = function;

		for (int i = 0; i < 8; ++i)
			writeInstruction(target, slot.b[i]);
	}

	//==============================READ==============================//

	instruction_t VMResources::readInstruction(const std::vector<instruction_t>& target, index_t & pc)
	{
		return target[pc++];
	}
	index_t VMResources::readIndex(const std::vector<instruction_t>& target, index_t & pc)
	{
		VMValue slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.m_Index;
	}
	float_t VMResources::readFloat(const std::vector<instruction_t>& target, index_t & pc)
	{
		VMValue slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.m_Float;
	}
	int_t VMResources::readInt(const std::vector<instruction_t>& target, index_t & pc)
	{
		VMValue slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.m_Int;
	}
	short_t VMResources::readShort(const std::vector<instruction_t>& target, index_t & pc)
	{
		VMValue slot;

		for (int i = 0; i < 2; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.m_Short;
	}
	byte_t VMResources::readByte(const std::vector<instruction_t>& target, index_t & pc)
	{
		return target[pc++];
	}

	native_t VMResources::readFunction(const std::vector<instruction_t>& target, index_t & pc)
	{
		VMValue slot;

		for (int i = 0; i < 8; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.m_Native;
	}

	hash_t VMResources::hash(const std::string & string, int seed)
	{
		return hash(string.c_str(), seed);
	}

	hash_t VMResources::hash(const char * string, int seed)
	{
		unsigned int hash = seed;
		while (*string)
		{
			hash = hash * 101 + *string++;
		}
		return hash;
	}
}
