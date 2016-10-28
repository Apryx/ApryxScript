#include "VMFrame.h"

namespace apryx {
	VMFrame::VMFrame(int localsAmount, int operandStackSize)
	{
		m_Locals.resize(localsAmount);

		m_OperandStack.reserve(operandStackSize);
	}
}