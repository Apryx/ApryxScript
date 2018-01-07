#include <iostream>

#include "bytecode\ByteCode.h"

#include "runtime\ByteReader.h"
#include "runtime\Runtime.h"

#include "runtime\ByteStack.h"

#include "memory\Class.h"
#include "memory\Field.h"
#include "memory\Function.h"
#include "memory\Type.h"

int main()
{
	using namespace apryx;

	Function mainFunction = Function(
		"main",
		Type(Type::Int),
		std::vector<Field>(),
		{
			(uint8_t)ByteCode::PushByte,
			(uint8_t)123,
			(uint8_t)ByteCode::IntReturn
		}
	);

	Class mainClass = Class(
		"Main",
		std::vector<Field>(),
		{mainFunction}
	);

	Runtime runtime;

	runtime.registerClass(mainClass);

	runtime.executeStatic("Main", "main()");

	std::cout << "Program exited with code "<< runtime.getStack().popInt() << std::endl;

	std::cin.get();
}

