#include "BytecodeTest.h"

#include "vm/VMValue.h"
#include "vm/ScriptVM.h"
#include "vm/VMResources.h"
#include "vm/VMWriter.h"
#include "vm/VMObject.h"
#include "vm/VMFunction.h"

namespace apryx {

	static bool print(std::vector<apryx::VMValue> &stack, int count)
	{
		apryx::VMValue slot;

		for (int i = 0; i < count; i++) {
			slot = stack.back(); stack.pop_back();
			LOG(slot);
		}

		return true;
	}

	void testBytecode()
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
			.pushglobal()
			.getfield("print")
			.invoke(1)
			.ret();

		VMFunction function(writer);

		ScriptVM vm;

		VMValue value;
		value.setType(VMValue::Type::NATIVE_FUNCTION);
		value.m_Native = print;

		vm.m_Globals->set("print", value);

		vm.execute(function);

		vm.dump();
	}
}