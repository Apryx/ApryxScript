#include "VMTypes.h"

#include <assert.h>

namespace apryx {
	void verify_types()
	{
		assert(sizeof(instruction_t) * CHAR_BIT == 8);
		assert(sizeof(index_t) == 4);
		assert(sizeof(float_t) == 4);
		assert(sizeof(short_t) == 2);
		assert(sizeof(byte_t) == 1);
		assert(sizeof(native_t) == 8);

		assert(sizeof(VMOperandSlot) == 12);
	}

	VMFrame::VMFrame(int localsAmount, int operandStackSize)
	{
		m_Locals.resize(localsAmount);
		m_OperandStack.resize(operandStackSize);
	}
}
