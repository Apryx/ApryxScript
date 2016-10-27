#include "VMResources.h"

namespace apryx {

	//==============================WRITE==============================//

	void VMResources::writeInstruction(std::vector<instruction_t>& target, instruction_t instruction)
	{
		target.push_back(instruction);
	}

	void VMResources::writeIndex(std::vector<instruction_t>& target, index_t i)
	{
		VMOperandSlot slot;
		slot.index = i;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeFloat(std::vector<instruction_t>& target, float_t f)
	{
		VMOperandSlot slot;
		slot.f = f;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeInt(std::vector<instruction_t>& target, int_t i)
	{
		VMOperandSlot slot;
		slot.i = i;

		for (int i = 0; i < 4; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeShort(std::vector<instruction_t>& target, short_t s)
	{
		VMOperandSlot slot;
		slot.s[0] = s;

		for (int i = 0; i < 2; ++i)
			writeInstruction(target, slot.b[i]);
	}

	void VMResources::writeByte(std::vector<instruction_t>& target, byte_t b)
	{

		writeInstruction(target, b);
	}

	void VMResources::writeFunction(std::vector<instruction_t>& target, native_t function)
	{
		VMOperandSlot slot;
		slot.n = function;

		for (int i = 0; i < 8; ++i)
			writeInstruction(target, slot.b[i]);
	}

	//==============================READ==============================//

	instruction_t VMResources::readInstruction(std::vector<instruction_t>& target, index_t & pc)
	{
		return target[pc++];
	}
	index_t VMResources::readIndex(std::vector<instruction_t>& target, index_t & pc)
	{
		VMOperandSlot slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.index;
	}
	float_t VMResources::readFloat(std::vector<instruction_t>& target, index_t & pc)
	{
		VMOperandSlot slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.f;
	}
	int_t VMResources::readInt(std::vector<instruction_t>& target, index_t & pc)
	{
		VMOperandSlot slot;

		for (int i = 0; i < 4; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.i;
	}
	short_t VMResources::readShort(std::vector<instruction_t>& target, index_t & pc)
	{
		VMOperandSlot slot;

		for (int i = 0; i < 2; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.s[0];
	}
	byte_t VMResources::readByte(std::vector<instruction_t>& target, index_t & pc)
	{
		return target[pc++];
	}

	native_t VMResources::readFunction(std::vector<instruction_t>& target, index_t & pc)
	{
		VMOperandSlot slot;

		for (int i = 0; i < 8; ++i) {
			slot.b[i] = target[pc++];
		}

		return slot.n;
	}
}
