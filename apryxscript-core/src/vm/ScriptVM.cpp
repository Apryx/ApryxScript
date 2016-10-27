#include "ScriptVM.h"
#include "VMResources.h"
#include "logger/log.h"

#define CHECK_MSG(value, message) if(!value){ERROR(message);}
#define CHECK(value) CHECK_MSG(value, "Failed!");

#define OPERATOR(TYPE, OP, TYPENAME) \
	{VMOperandSlot a = pop();VMOperandSlot b = pop(); \
	CHECK_MSG(a.m_Type == b.m_Type, "Incompatible types"); CHECK_MSG(a.m_Type == a.TYPENAME, "Incorrect types.");\
	VMOperandSlot r;r.TYPE = a. TYPE OP b. TYPE;r.m_Type = a.TYPENAME; push(r); }
namespace apryx {

	ScriptVM::ScriptVM(std::vector<instruction_t> ins) : m_Instructions(ins)
	{
		VMFrame frame(0,0);
		m_Stack.push_back(std::move(frame));
	}

	void ScriptVM::execute()
	{
		bool running	=	true;
		index_t pc		=	0;

		while (running) {
			instruction_t instruction = m_Instructions[pc++];
			VMOperandSlot slot;

			switch (instruction) {
				//========================================PUSHING========================================//
			case PUSH_BYTE: //TODO all this can be done with just a single template read<N>(); that reads N bytes
				slot.i = (int_t) VMResources::readByte(m_Instructions, pc);
				slot.m_Type = slot.INT;
				push(slot);
				break;
			case PUSH_SHORT:
				slot.i = (int_t)VMResources::readShort(m_Instructions, pc);
				slot.m_Type = slot.INT;
				push(slot);
				break;
			case PUSH_INT:
				slot.i = (int_t)VMResources::readInt(m_Instructions, pc);
				slot.m_Type = slot.INT;
				push(slot);
				break;
			case PUSH_FLOAT:
				slot.f = VMResources::readFloat(m_Instructions, pc);
				slot.m_Type = slot.FLOAT;
				push(slot);
				break;
			case PUSH_NATIVE:
				slot.n = VMResources::readFunction(m_Instructions, pc);
				slot.m_Type = slot.NATIVE_FUNCTION;
				push(slot);
				break;

				//========================================INTEGER OPERATORS========================================//
			case IADD:
				OPERATOR(i, +, INT);
				break;
			case ISUB:
				OPERATOR(i, -, INT);
				break;
			case IMUL:
				OPERATOR(i, *, INT);
				break;
			case IDIV:
				OPERATOR(i, /, INT);
				break;

				//========================================FLOAT OPERATORS========================================//
			case FADD:
				OPERATOR(f, +, FLOAT);
				break;
			case FSUB:
				OPERATOR(f, -, FLOAT);
				break;
			case FMUL:
				OPERATOR(f, *, FLOAT);
				break;
			case FDIV:
				OPERATOR(f, / , FLOAT);
				break;

				//======================================== Invocation ========================================//

			case INVOKE_NATIVE:
			{
				VMOperandSlot function = pop();
				CHECK_MSG(function.m_Type == function.NATIVE_FUNCTION, "Not a native function");
				int_t b = (int_t) VMResources::readByte(m_Instructions, pc);
				function.n(m_Stack.back().m_OperandStack, b);
			}
				break;

				//======================================== Helpfull stuff ========================================//

			case SWAP: 
			{
				VMOperandSlot a = pop();
				VMOperandSlot b = pop();
				push(a);
				push(b);
			}
				break;
			case DUP:
			{
				VMOperandSlot a = top();
				push(a);
				push(a);
			}
			break;
			case POP:
			{
				vpop();
			}
			break;

				//========================================CONVERTERS========================================//
			case F2I:
			{
				VMOperandSlot &slot = top();
				slot.i = (int)slot.f;
				slot.m_Type = slot.INT;
			}
				break;
			case I2F:
			{
				VMOperandSlot &slot = top();
				slot.f = (int)slot.i;
				slot.m_Type = slot.FLOAT;
			}
				break;

				//========================================VM INSTRUCTIONS========================================//
			case DUMP:
				for (auto &frame : m_Stack) {
					for (auto &stack : frame.m_OperandStack) {
						LOG(" > " << std::hex << stack.i << std::dec);
					}
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
