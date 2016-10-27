#pragma once
#include "VMTypes.h"
#include "VMResources.h"

namespace apryx {
	class VMWriter {
	public:
		std::vector<instruction_t> m_Target;

	public:
		inline VMWriter &push(float_t f)
		{
			VMResources::writeInstruction(m_Target, PUSH_FLOAT);
			VMResources::writeFloat(m_Target, f);
			return *this;
		}
		inline VMWriter &push(int_t i)
		{
			VMResources::writeInstruction(m_Target, PUSH_INT);
			VMResources::writeInt(m_Target, i);
			return *this;
		}
		inline VMWriter &push(short_t s)
		{
			VMResources::writeInstruction(m_Target, PUSH_SHORT);
			VMResources::writeShort(m_Target, s);
			return *this;
		}
		inline VMWriter &push(byte_t b)
		{
			VMResources::writeInstruction(m_Target, PUSH_BYTE);
			VMResources::writeByte(m_Target, b);
			return *this;
		}
		inline VMWriter &push(native_t n)
		{
			VMResources::writeInstruction(m_Target, PUSH_NATIVE);
			VMResources::writeFunction(m_Target, n);
			return *this;
		}

		inline VMWriter &dup()
		{
			VMResources::writeInstruction(m_Target, DUP);
			return *this;
		}
		inline VMWriter &pop()
		{
			VMResources::writeInstruction(m_Target, POP);
			return *this;
		}
		inline VMWriter &swap()
		{
			VMResources::writeInstruction(m_Target, SWAP);
			return *this;
		}
		inline VMWriter &f2i()
		{
			VMResources::writeInstruction(m_Target, F2I);
			return *this;
		}
		inline VMWriter &i2f()
		{
			VMResources::writeInstruction(m_Target, I2F);
			return *this;
		}

		inline VMWriter &iadd()
		{
			VMResources::writeInstruction(m_Target, IADD);
			return *this;
		}
		inline VMWriter &isub()
		{
			VMResources::writeInstruction(m_Target, ISUB);
			return *this;
		}
		inline VMWriter &imul()
		{
			VMResources::writeInstruction(m_Target, IMUL);
			return *this;
		}
		inline VMWriter &idiv()
		{
			VMResources::writeInstruction(m_Target, IDIV);
			return *this;
		}

		inline VMWriter &fadd()
		{
			VMResources::writeInstruction(m_Target, FADD);
			return *this;
		}
		inline VMWriter &fsub()
		{
			VMResources::writeInstruction(m_Target, FSUB);
			return *this;
		}
		inline VMWriter &fmul()
		{
			VMResources::writeInstruction(m_Target, FMUL);
			return *this;
		}
		inline VMWriter &fdiv()
		{
			VMResources::writeInstruction(m_Target, FDIV);
			return *this;
		}

		inline VMWriter &invokeNative(byte_t args)
		{
			VMResources::writeInstruction(m_Target, INVOKE_NATIVE);
			VMResources::writeByte(m_Target, args);
			return *this;
		}
		inline VMWriter &invoke(byte_t args)
		{
			VMResources::writeInstruction(m_Target, INVOKE);
			VMResources::writeByte(m_Target, args);
			return *this;
		}

		inline VMWriter &exit()
		{
			VMResources::writeInstruction(m_Target, EXIT);
			return *this;
		}

	};
}