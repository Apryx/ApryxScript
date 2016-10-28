#pragma once

#include "VMTypes.h"

namespace apryx {
	class VMWriter;

	struct VMFunction {
		index_t m_LocalCount;
		index_t m_StackHeight;
		std::vector<instruction_t> m_Instructions;
		std::vector<std::string> m_Constants;

	public:
		VMFunction(const VMWriter &writer);
	};
}