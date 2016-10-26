#pragma once

#include <vector>

#include "VMTypes.h"
#include "VMStack.h"

namespace apryx {

	class ScriptVM {
		VMStack m_Stack;
		std::vector<instruction_t> m_Instructions;

	public:
		ScriptVM(std::vector<instruction_t>);

		void execute();

		friend class VMResources;
	};
}