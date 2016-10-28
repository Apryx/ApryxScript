#include "VMFunction.h"
#include "VMWriter.h"

namespace apryx {

	VMFunction::VMFunction(const VMWriter &writer)
		:
		m_LocalCount(writer.getLocals()),
		m_StackHeight(writer.getStackHeight()),
		m_Instructions(writer.getInstructions()),
		m_Constants(writer.getConstants())
	{

	}
}
