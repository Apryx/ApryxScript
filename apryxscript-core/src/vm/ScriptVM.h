#pragma once

#include <vector>

#include "VMTypes.h"
#include "VMValue.h"
#include "VMObject.h"
#include "VMFrame.h"
#include "logger/log.h"

#include "VMFunction.h"

namespace apryx {

	class ScriptVM {
		std::vector<VMFrame> m_Stack;
		std::shared_ptr<VMObject> m_Globals;

	public:
		ScriptVM();

		//Note: Execute should have a function to execute
		//so that it can use recursion to execute lots of functions!
		void execute(const VMFunction &function);

		//Extra usefull stuff
	public:
		void gc();
		index_t newInstance();

		void dump();

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

		inline void setlocal(int index, const VMOperandSlot &s)
		{
			m_Stack.back().m_Locals[index] = s;
		}
		inline VMOperandSlot getlocal(int index)
		{
			return m_Stack.back().m_Locals[index];
		}

		friend class VMResources;
	};
}