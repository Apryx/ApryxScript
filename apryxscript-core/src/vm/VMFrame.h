#pragma once

#include "VMTypes.h"
#include "VMValue.h"

namespace apryx {

	struct VMFrame {
		std::vector<VMValue> m_OperandStack;
		std::vector<VMValue> m_Locals;

	public:
		VMFrame(int localsAmount, int operandStackSize);
	};
}