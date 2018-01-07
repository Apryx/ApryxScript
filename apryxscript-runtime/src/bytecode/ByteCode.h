#pragma once

#include <vector>

namespace apryx {

	typedef std::vector<uint8_t> ByteSequence;

	enum class ByteCode : unsigned char {
		// Pushing and popping constants
		PushInt = 0x01,
		PushShort,
		PushByte,

		// Misc helper stuff
		Duplicate = 0x20,
		Pop,
		Swap,

		// Operators
		IntAdd = 0x40,
		IntSubtract,
		IntMultiply,
		IntDivide,

		// Invokation
		InvokeNative = 0x7A,
		InvokeVirtual,

		// Saving and loading data (locals)
		IntStore= 0x80,
		IntLoad,

		// Fields (class parameters)
		PutField = 0x90,
		GetField,

		// Returns
		VoidReturn = 0xA0,
		IntReturn,


		// Last helpers and debug tools
		DumpStack = 0xF0,
	};

}