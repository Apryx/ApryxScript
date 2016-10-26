#pragma once

#define EXIT		0x00		//Terminates the VM
#define HALT		0x01		//Pauses the VM
#define DUMP		0x02		//Pauses the VM

#define PUSH_BYTE	0x10		//Pushes an byte onto the stack
#define PUSH_SHORT	0x11		//Pushes an short onto the stack
#define PUSH_INT	0x12		//Pushes an int onto the stack
#define PUSH_FLOAT	0x13		//Pushes an float onto the stack

#define POP			0x20		//Pops the top of the stack

#define SWAP		0x40		//Swap the two things

#define IADD		0x50		//Add two integers
#define ISUB		0x51		//Subtract two integers
#define IMUL		0x52		//Multiply two integers
#define IDIV		0x53		//Divide two integers

#define FADD		0x60		//Add two floats
#define FSUB		0x61		//Subtract two floats
#define FMUL		0x62		//Multiply two floats
#define FDIV		0x63		//Divide two floats

#define I2F			0x70		//Convert integer into float
#define F2I			0x71		//Convert float into integer

#include <string>

namespace apryx {
	typedef unsigned char instruction_t;
	typedef unsigned int index_t;

	typedef float	float_t;
	typedef int		int_t;
	typedef short	short_t;
	typedef char	byte_t;
	
	typedef std::string string_t;

	void verify_types();
}