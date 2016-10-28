#pragma once

#include <vector>

#include "VMTypes.h"
#include "VMValue.h"
#include "VMObject.h"
#include "VMFrame.h"
#include "logger/log.h"

namespace apryx {

	class ScriptVM {
		std::vector<VMFrame> m_Stack;

		std::vector<VMObject> m_Objects;
		std::vector<instruction_t> m_Instructions;
	public:
		ScriptVM(std::vector<instruction_t>);

		//Note: Execute should have a function to execute
		//so that it can use recursion to execute lots of functions!
		void execute();

		//Extra usefull stuff
	public:
		void gc();
		index_t newInstance();

		inline void push(const VMOperandSlot &s)
		{
			m_Stack.back().m_OperandStack.push_back(s);
		}
		inline void push(VMOperandSlot &&s)
		{
			m_Stack.back().m_OperandStack.push_back(s);
		}
		inline VMOperandSlot pop()
		{
			VMOperandSlot slot;

			slot = m_Stack.back().m_OperandStack.back();
			m_Stack.back().m_OperandStack.pop_back();

			return std::move(slot);
		}
		inline void vpop()
		{
			m_Stack.back().m_OperandStack.pop_back();
		}
		inline VMOperandSlot &top()
		{
			return m_Stack.back().m_OperandStack.back();
		}

		friend class VMResources;
	};
}