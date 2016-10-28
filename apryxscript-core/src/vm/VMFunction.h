#pragma once

#include "VMTypes.h"

namespace apryx {
	struct VMFunction {
		index_t m_LocalCount;
		index_t m_StackHeigth;
		std::vector<instruction_t> m_Instructions;
	};
}