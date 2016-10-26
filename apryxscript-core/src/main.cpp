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
#include "vm/VMStack.h"
#include "vm/VMResources.h"


int main(void)
{
	using namespace apryx;

	verify_types();

	std::vector<instruction_t> target;

	VMResources::writeInstruction(target, PUSH_BYTE);
	VMResources::writeByte(target, 3);
	VMResources::writeInstruction(target, PUSH_FLOAT);
	VMResources::writeFloat(target, 3);
	VMResources::writeInstruction(target, PUSH_FLOAT);
	VMResources::writeFloat(target, 4);
	VMResources::writeInstruction(target, FMUL);
	VMResources::writeInstruction(target, SWAP);
	VMResources::writeInstruction(target, I2F);
	VMResources::writeInstruction(target, FADD);
	VMResources::writeInstruction(target, DUMP);
	VMResources::writeInstruction(target, EXIT);

	ScriptVM vm(target);
	vm.execute();

	WAIT();
	return 0;
}