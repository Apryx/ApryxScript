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
		LOG(slot);
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
		.pushglobal()
		.push(2)
		.setfield("a")
		.pushglobal()
		.push(4)
		.setfield("b")

		.pushglobal()
		.getfield("a")
		.pushglobal()
		.getfield("b")

		.iadd()
		.push(print)
		.invokeNative(1)
		.ret();

	VMFunction function(writer);

	ScriptVM vm;

	vm.execute(function);

	WAIT();
	return 0;
}