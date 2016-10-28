#include "ScriptVM.h"
#include "VMResources.h"
#include "logger/log.h"

#define CHECK_MSG(value, message) if(!(value)){ERROR(message);}
#define CHECK(value) CHECK_MSG(value, "Failed!");

#define OPERATOR(TYPE, OP, TYPENAME) \
	{VMOperandSlot a = pop();VMOperandSlot b = pop(); \
	CHECK_MSG(a.getType() == b.getType(), "Incompatible types"); CHECK_MSG(a.getType() == VMValue::Type::TYPENAME, "Incorrect types.");\
	VMOperandSlot r;r.TYPE = a. TYPE OP b. TYPE;r.setType( VMValue::Type::TYPENAME); push(r); }

namespace apryx {

	ScriptVM::ScriptVM()
	{
		m_Globals = std::make_shared<VMObject>();
	}

	void ScriptVM::execute(const VMFunction &function)
	{
		//Push a frame to the stack
		VMFrame frame(function.m_LocalCount, function.m_StackHeight);
		m_Stack.push_back(std::move(frame));

		bool running	=	true;
		index_t pc		=	0;

		//Make a reference for easy stuff
		const std::vector<instruction_t> &instructions = function.m_Instructions;

		while (running) {
			instruction_t instruction = instructions[pc++];
			VMOperandSlot slot;

			switch (instruction) {
				//========================================PUSHING========================================//
			case PUSH_BYTE: //TODO all this can be done with just a single template read<N>(); that reads N bytes
				slot.m_Int = (int_t)VMResources::readByte(instructions, pc);
				slot.setType(VMValue::Type::INT);
				push(slot);
				break;
			case PUSH_SHORT:
				slot.m_Int = (int_t)VMResources::readShort(instructions, pc);
				slot.setType(VMValue::Type::INT);
				push(slot);
				break;
			case PUSH_INT:
				slot.m_Int = (int_t)VMResources::readInt(instructions, pc);
				slot.setType(VMValue::Type::INT);
				push(slot);
				break;
			case PUSH_FLOAT:
				slot.m_Float = VMResources::readFloat(instructions, pc);
				slot.setType(VMValue::Type::FLOAT);
				push(slot);
				break;
			case PUSH_NATIVE:
				slot.m_Native = VMResources::readFunction(instructions, pc);
				slot.setType(VMValue::Type::NATIVE_FUNCTION);
				push(slot);
				break;
			case PUSH_NULL:
				slot = VMOperandSlot();
				slot.setType(VMOperandSlot::Type::OBJECT);
				push(slot);
				break;
			case PUSH_GLOBAL:
				slot = VMOperandSlot();
				slot.setType(VMOperandSlot::Type::OBJECT);
				slot.m_VMObject = m_Globals;
				push(slot);
				break;

				//========================================INTEGER OPERATORS========================================//
			case IADD:
				OPERATOR(m_Int, +, INT);
				break;
			case ISUB:
				OPERATOR(m_Int, -, INT);
				break;
			case IMUL:
				OPERATOR(m_Int, *, INT);
				break;
			case IDIV:
				OPERATOR(m_Int, / , INT);
				break;

				//========================================FLOAT OPERATORS========================================//
			case FADD:
				OPERATOR(m_Float, +, FLOAT);
				break;
			case FSUB:
				OPERATOR(m_Float, -, FLOAT);
				break;
			case FMUL:
				OPERATOR(m_Float, *, FLOAT);
				break;
			case FDIV:
				OPERATOR(m_Float, / , FLOAT);
				break;

				//======================================== Invocation ========================================//

			case INVOKE_NATIVE:
			{
				VMOperandSlot function = pop();
				CHECK_MSG(function.getType() == VMValue::Type::NATIVE_FUNCTION, "Not a native function");
				int_t b = (int_t)VMResources::readByte(instructions, pc);
				function.m_Native(m_Stack.back().m_OperandStack, b);
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
			case RET:
			{
				if (m_Stack.back().m_OperandStack.size() > 0) {
					dump();
					ERROR("Stackheight != 0");
				}
				else {
					m_Stack.pop_back();
					return;
				}
			}
			break;

			//========================================Fields and locals========================================//
			case SETFIELD:
			{
				VMOperandSlot value = pop();
				VMOperandSlot obj = pop();
				int_t index = (int_t)VMResources::readShort(instructions, pc);
				CHECK_MSG(obj.getType() == VMOperandSlot::Type::OBJECT, "Not an object to set the field to");
				
				//These should be runtime exceptions
				CHECK_MSG(obj.m_VMObject != nullptr, "Nullpointer exception!");

				std::string c = function.m_Constants[index];
				obj.m_VMObject->m_Objects[c] = value;
			}
				break;
			case GETFIELD:
			{
				VMOperandSlot obj = pop();
				int_t index = (int_t)VMResources::readShort(instructions, pc);

				CHECK_MSG(obj.getType() == VMOperandSlot::Type::OBJECT, "Not an object to set the field to");

				//These should be runtime exceptions
				CHECK_MSG(obj.m_VMObject != nullptr, "Nullpointer exception!");

				std::string c = function.m_Constants[index];
				push(obj.m_VMObject->m_Objects[c]);
			}
				break;

			case SETLOCAL:
			{
				VMOperandSlot value = pop();
				int_t index = (int_t)VMResources::readByte(instructions, pc);
				setlocal(index, value);
			}
			break;
			case GETLOCAL:
			{
				int_t index = (int_t)VMResources::readByte(instructions, pc);
				push(getlocal(index));
			}
				break;

				//========================================CONVERTERS========================================//
			case F2I:
			{
				VMOperandSlot &slot = top();
				//TODO type checks
				slot.m_Int = (int)slot.m_Float;
				slot.setType(VMValue::Type::INT);
			}
				break;
			case I2F:
			{
				VMOperandSlot &slot = top();
				//TODO type checks
				slot.m_Float = (int)slot.m_Int;
				slot.setType(VMValue::Type::FLOAT);
			}
				break;

				//========================================VM INSTRUCTIONS========================================//
			case DUMP:
				dump();
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

	void ScriptVM::dump()
	{
		LOG("Current stack:");
		for (auto &frame : m_Stack) {
			int o = 0;
			for (auto &stack : frame.m_OperandStack) {
				LOG(o++ << " > " << std::hex << stack.m_Long << std::dec);
			}
		}
	}

	void ScriptVM::gc()
	{

	}

	index_t ScriptVM::newInstance()
	{
		return 0;
	}
}
