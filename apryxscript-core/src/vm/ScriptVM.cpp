#include "ScriptVM.h"
#include "VMResources.h"
#include "logger/log.h"

#define OPERATOR(TYPE, OP) \
	{VMSlot a = m_Stack.back(); m_Stack.pop_back();VMSlot b = m_Stack.back(); m_Stack.pop_back();\
	VMSlot r;r.TYPE = a. TYPE OP b. TYPE; m_Stack.push_back(r); }

namespace apryx {

	ScriptVM::ScriptVM(std::vector<instruction_t> ins) : m_Instructions(ins)
	{ }

	void ScriptVM::execute()
	{
		bool running	=	true;
		index_t pc		=	0;

		while (running) {
			instruction_t instruction = m_Instructions[pc++];
			VMSlot slot;

			switch (instruction) {
				//========================================PUSHING========================================//
			case PUSH_BYTE:
				slot.i = VMResources::readByte(m_Instructions, pc);
				m_Stack.push_back(slot);
				break;
			case PUSH_SHORT:
				slot.i = VMResources::readShort(m_Instructions, pc);
				m_Stack.push_back(slot);
				break;
			case PUSH_INT:
				slot.i = VMResources::readInt(m_Instructions, pc);
				m_Stack.push_back(slot);
				break;
			case PUSH_FLOAT:
				slot.f = VMResources::readFloat(m_Instructions, pc);
				m_Stack.push_back(slot);
				break;

				//========================================INTEGER OPERATORS========================================//
			case IADD:
				OPERATOR(i, +);
				break;
			case ISUB:
				OPERATOR(i, -);
				break;
			case IMUL:
				OPERATOR(i, *);
				break;
			case IDIV:
				OPERATOR(i, /);
				break;

				//========================================FLOAT OPERATORS========================================//
			case FADD:
				OPERATOR(f, +);
				break;
			case FSUB:
				OPERATOR(f, -);
				break;
			case FMUL:
				OPERATOR(f, *);
				break;
			case FDIV:
				OPERATOR(f, / );
				break;

				//======================================== SWAP ========================================//

			case SWAP: 
			{
				VMSlot a = m_Stack.back(); m_Stack.pop_back();
				VMSlot b = m_Stack.back(); m_Stack.pop_back();
				m_Stack.push_back(a);
				m_Stack.push_back(b);
			}
				break;

				//========================================CONVERTERS========================================//
			case F2I:
				slot = m_Stack.back(); m_Stack.pop_back();
				slot.i = (int)slot.f;
				m_Stack.push_back(slot);
				break;
			case I2F:
				slot = m_Stack.back(); m_Stack.pop_back();
				slot.f = (float)slot.i;
				m_Stack.push_back(slot);
				break;

				//========================================VM INSTRUCTIONS========================================//
			case DUMP:
				for (auto &s : m_Stack) {
					LOG(" > " << s.i << " " << s.f);
				}
				break;
			case EXIT:
				running = false;
				break;
			default:
				LOG_ERROR("Unimplemented instruction: " << std::hex << (unsigned int) instruction << std::dec);
				return;
			}
		}
	}
}
