
#include "Runtime.h"

#include <iostream>
#include <stack>

#include <assert.h>

namespace apryx {
	
	void Runtime::registerClass(Class cls)
	{
		m_RegisteredClasses.push_back(std::move(cls));
	}

	Class & Runtime::getClass(int i)
	{
		return m_RegisteredClasses[i];
	}

	void Runtime::dumpStack()
	{
		while (!m_Stack.empty()) {
			std::cout << m_Stack.popInt() << std::endl;
		}
	}

	int Runtime::getClassIndex(const std::string & name)
	{
		for (int i = 0; i < m_RegisteredClasses.size(); i++)
			if (m_RegisteredClasses[i].name() == name)
				return i;
		return -1;
	}

	size_t Runtime::execute(const FunctionStatement & function)
	{
		ByteReader reader = ByteReader(function.code());

		size_t stackStartHeight = m_Stack.height();

		while (!reader.done()){
			ByteCode code = reader.readCode();
			
			switch (code)
			{
			case ByteCode::PushByte:
			{
				int8_t n = reader.readByte();

				m_Stack.pushInt((int32_t)n);

				break;
			}

			case ByteCode::IntAdd:
			{
				int32_t a = m_Stack.popInt();
				int32_t b = m_Stack.popInt();

				m_Stack.pushInt(a + b);

				break;
			}
			case ByteCode::IntSubtract:
			{
				int32_t a = m_Stack.popInt();
				int32_t b = m_Stack.popInt();

				m_Stack.pushInt(b - a);

				break;
			}
			case ByteCode::IntMultiply:
			{
				int32_t a = m_Stack.popInt();
				int32_t b = m_Stack.popInt();

				m_Stack.pushInt(a * b);

				break;
			}
			case ByteCode::IntDivide:
			{
				int32_t a = m_Stack.popInt();
				int32_t b = m_Stack.popInt();

				m_Stack.pushInt(b / a);

				break;
			}


			case ByteCode::IntReturn:
			{
				assert(m_Stack.height() == stackStartHeight + sizeof(int32_t));
				assert(function.returnType().getNative() == Type::Int);
				return sizeof(int32_t);
			}

			case ByteCode::VoidReturn:
			{
				assert(m_Stack.height() == stackStartHeight);
				assert(function.returnType().getNative() == Type::Void);
				return 0;
			}

			case ByteCode::DumpStack:
			{
				dumpStack();
				break;
			}
			default:
				throw "Invalid bytecode";
			}

		}

		throw "Function not returning.";
	}

	void Runtime::executeStatic(const std::string & className, const std::string & functionSignature)
	{
		int index = getClassIndex(className);

		if (index < 0)
			return;

		Class &cls = getClass(index);

		int functionIndex = cls.getFunctionIndexBySignature(functionSignature);

		if (functionIndex < 0)
			return;

		FunctionStatement &function = cls.getFunction(functionIndex);

		execute(function);
	}


}