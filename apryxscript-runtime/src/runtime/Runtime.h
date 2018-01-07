#pragma once

#include "ByteReader.h"

#include "memory/Class.h"
#include "ByteStack.h"

namespace apryx {

	class Runtime {
		std::vector<Class> m_RegisteredClasses;

		ByteStack m_Stack;
	public:
		void registerClass(Class cls);
		int getClassIndex(const std::string &name);
		Class &getClass(int i);

	private:
		void dumpStack();
	
	public:
		size_t execute(const Function &function);

		void executeStatic(
			const std::string &className,
			const std::string &signature
		);

		ByteStack &getStack() { return m_Stack; }
	};

}