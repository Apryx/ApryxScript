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
#include "vm/VMObject.h"
#include "vm/VMFunction.h"

bool add(std::vector<apryx::VMValue> &stack, int count)
{
	apryx::VMValue slot;
	int res = 0;
	for (int i = 0; i < count; i++) {
		slot = stack.back(); stack.pop_back();
		res += slot.m_Int;
	}
	slot.m_Int = res;
	stack.push_back(slot);
	return true;
}

bool print(std::vector<apryx::VMValue> &stack, int count)
{
	apryx::VMValue slot;

	for (int i = 0; i < count; i++) {
		slot = stack.back(); stack.pop_back();
		switch (slot.getType()) {
		case  apryx::VMValue::Type::FLOAT:
			LOG(slot.m_Float);
			break;
		case apryx::VMValue::Type::INT:
			LOG(slot.m_Int);
			break;
		case apryx::VMValue::Type::NATIVE_FUNCTION:
			LOG("nat " << slot.m_Native);
			break;
		default:
			LOG(std::hex << slot.m_Long << std::dec);
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
		.push(2)
		.push(4)
		.iadd()
		.setlocal(0)
		.getlocal(0)
		.push(print)
		.invokeNative(1)
		.ret();

	VMFunction function(writer);

	ScriptVM vm;

	vm.execute(function);

	WAIT();
	return 0;
}