//TODO move this to different project (apryxscript-application)

#include "logger/log.h"
#include "lexer/Lexer.h"
#include "parser/Parser.h"
#include "ast/Statement.h"
#include "runtime/Runtime.h"

#include <memory>
#include <fstream>
#include <sstream>

#include "vm/ScriptVM.h"
#include "vm/VMResources.h"
#include "vm/VMWriter.h"


bool add(apryx::VMOperandStack &stack, int count)
{
	apryx::VMOperandSlot slot;
	int res = 0;
	for (int i = 0; i < count; i++) {
		slot = stack.back(); stack.pop_back();
		res += slot.i;
	}
	slot.i = res;
	stack.push_back(slot);
	return true;
}

bool print(apryx::VMOperandStack &stack, int count)
{
	apryx::VMOperandSlot slot;

	for (int i = 0; i < count; i++) {
		slot = stack.back(); stack.pop_back();
		switch (slot.m_Type) {
		case slot.FLOAT:
			LOG(slot.f);
			break;
		case slot.INT:
			LOG(slot.i);
			break;
		case slot.FUNCTION:
			LOG(slot.i);
			break;
		case slot.NATIVE_FUNCTION:
			LOG("nat" << slot.f);
			break;
		default:
			LOG(std::hex << slot.l << std::dec);
			break;
		}
	}

	return true;
}

int main(void)
{
	using namespace apryx;

	//Make sure the VM does what its supposed to do 

	verify_types();

	VMWriter writer;
	writer
		.push(2.0f)
		.push(1)
		.swap()
		.f2i()
		.iadd()
		.push(print)
		.invokeNative(1)
		.exit();

	ScriptVM vm(writer.m_Target);
	vm.execute();

	WAIT();
	return 0;
}