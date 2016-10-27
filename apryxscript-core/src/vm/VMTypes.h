#pragma once

#define EXIT			0x00		//Terminates the VM
#define HALT			0x01		//Pauses the VM
#define DUMP			0x02		//Pauses the VM

#define PUSH_BYTE		0x10		//Pushes an byte onto the stack
#define PUSH_SHORT		0x11		//Pushes an short onto the stack
#define PUSH_INT		0x12		//Pushes an int onto the stack
#define PUSH_FLOAT		0x13		//Pushes an float onto the stack
#define PUSH_NATIVE		0x14		//Pushes a native on to the stack

#define POP				0x20		//Pops the top of the stack
#define DUP				0x21		//Pops the top of the stack
#define SWAP			0x22		//Swap the two things

#define IADD			0x50		//Add two integers
#define ISUB			0x51		//Subtract two integers
#define IMUL			0x52		//Multiply two integers
#define IDIV			0x53		//Divide two integers

#define FADD			0x60		//Add two floats
#define FSUB			0x61		//Subtract two floats
#define FMUL			0x62		//Multiply two floats
#define FDIV			0x63		//Divide two floats

#define I2F				0x70		//Convert integer into float
#define F2I				0x71		//Convert float into integer

#define INVOKE_NATIVE	0xA0		//Invoke native function (takes an extra byte, arg count)
#define INVOKE			0xA1		//Invoke native function (takes an extra byte, arg count)

#include <string>
#include <vector>

namespace apryx {

	typedef unsigned char instruction_t;
	typedef unsigned int index_t;

	typedef double	double_t;
	typedef long long long_t;
	typedef float	float_t;
	typedef int		int_t;
	typedef short	short_t;
	typedef char	byte_t;
	typedef std::string string_t;

	struct VMValue;
	struct VMFrame;

	typedef VMValue VMOperandSlot;
	typedef std::vector<VMOperandSlot> VMOperandStack;
	typedef std::vector<VMValue> VMLocals;
	typedef std::vector<VMFrame> VMStack;
	typedef bool (*native_t)(VMOperandStack&, int); //The stack, and the arguments, returning whether it succeeded or not

#pragma pack(push, 4)
	struct VMValue {
		union {
			//32 bit
			float_t f;
			int_t i;

			short_t s[4];
			byte_t b[8];
			index_t index;

			//64 bit
			double_t d;
			long_t l;
			native_t n;

			struct {
				int_t cls;	//Class that it was created from
				int_t ref;	//Object reference
			} obj;
		};
		enum {
			UNSET,
			INT,
			FLOAT,
			
			NATIVE_FUNCTION,
			FUNCTION,
			OBJECT
		} m_Type;

	};

	struct VMObject {
		int_t refCount = 0;
		std::map<int_t, VMValue> m_Objects;
	};

	struct VMFrame {
		VMOperandStack m_OperandStack;
		VMLocals m_Locals;

	public:
		VMFrame(int localsAmount, int operandStackSize);
	};

#pragma pack(pop)

	void verify_types();
}