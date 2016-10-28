#pragma once
#include "VMTypes.h"
#include "VMResources.h"
#include "logger/log.h"

namespace apryx {
	class VMWriter {
	private:
		int m_CurrentStackHeight = 0;
		int m_MaxStackHeight = 0;
		int m_MaxLocals = 0;
		std::vector<instruction_t> m_Target;
		std::vector<std::string> m_Constants;
	public:
		inline VMWriter &push(float_t f)
		{
			VMResources::writeInstruction(m_Target, PUSH_FLOAT);
			VMResources::writeFloat(m_Target, f);
			stack(1);
			return *this;
		}
		inline VMWriter &push(int_t i)
		{
			VMResources::writeInstruction(m_Target, PUSH_INT);
			VMResources::writeInt(m_Target, i);
			stack(1);
			return *this;
		}
		inline VMWriter &push(short_t s)
		{
			VMResources::writeInstruction(m_Target, PUSH_SHORT);
			VMResources::writeShort(m_Target, s);
			stack(1);
			return *this;
		}
		inline VMWriter &push(byte_t b)
		{
			VMResources::writeInstruction(m_Target, PUSH_BYTE);
			VMResources::writeByte(m_Target, b);
			stack(1);
			return *this;
		}
		inline VMWriter &push(native_t n)
		{
			VMResources::writeInstruction(m_Target, PUSH_NATIVE);
			VMResources::writeFunction(m_Target, n);
			stack(1);
			return *this;
		}
		inline VMWriter &pushglobal()
		{
			VMResources::writeInstruction(m_Target, PUSH_GLOBAL);
			stack(1);
			return *this;
		}
		inline VMWriter &pushnull()
		{
			VMResources::writeInstruction(m_Target, PUSH_NULL);
			stack(1);
			return *this;
		}

		inline VMWriter &dup()
		{
			VMResources::writeInstruction(m_Target, DUP);
			stack(1);
			return *this;
		}
		inline VMWriter &pop()
		{
			VMResources::writeInstruction(m_Target, POP);
			stack(-1);
			return *this;
		}
		inline VMWriter &swap()
		{
			VMResources::writeInstruction(m_Target, SWAP);
			stack(-2);
			stack(2);
			return *this;
		}
		inline VMWriter &f2i()
		{
			VMResources::writeInstruction(m_Target, F2I);
			stack(-1);
			stack(1);
			return *this;
		}
		inline VMWriter &i2f()
		{
			VMResources::writeInstruction(m_Target, I2F);
			stack(-1);
			stack(1);
			return *this;
		}

		inline VMWriter &iadd()
		{
			VMResources::writeInstruction(m_Target, IADD);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &isub()
		{
			VMResources::writeInstruction(m_Target, ISUB);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &imul()
		{
			VMResources::writeInstruction(m_Target, IMUL);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &idiv()
		{
			VMResources::writeInstruction(m_Target, IDIV);
			stack(-2);
			stack(1);
			return *this;
		}

		inline VMWriter &fadd()
		{
			VMResources::writeInstruction(m_Target, FADD);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &fsub()
		{
			VMResources::writeInstruction(m_Target, FSUB);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &fmul()
		{
			VMResources::writeInstruction(m_Target, FMUL);
			stack(-2);
			stack(1);
			return *this;
		}
		inline VMWriter &fdiv()
		{
			VMResources::writeInstruction(m_Target, FDIV);
			stack(-2);
			stack(1);
			return *this;
		}

		inline VMWriter &invoke(byte_t args)
		{
			VMResources::writeInstruction(m_Target, INVOKE);
			VMResources::writeByte(m_Target, args);
			stack(-(args + 1));
			stack(1);	//TODO TODO TODO functions always have a returntype!
			return *this;
		}

		inline VMWriter &setlocal(byte_t index)
		{
			VMResources::writeInstruction(m_Target, SETLOCAL);
			VMResources::writeByte(m_Target, index);
			local(index);
			stack(-1);
			return *this;
		}
		inline VMWriter &getlocal(byte_t index)
		{
			VMResources::writeInstruction(m_Target, GETLOCAL);
			VMResources::writeByte(m_Target, index);
			local(index);
			stack(1);
			return *this;
		}
		
		inline VMWriter &setfield(const std::string &field)
		{
			VMResources::writeInstruction(m_Target, SETFIELD);
			VMResources::writeShort(m_Target, constant(field));
			stack(-2);
			return *this;
		}
		inline VMWriter &getfield(const std::string &field)
		{
			VMResources::writeInstruction(m_Target, GETFIELD);
			VMResources::writeShort(m_Target, constant(field));
			stack(-1);
			stack(1);
			return *this;
		}


		inline VMWriter &exit()
		{
			VMResources::writeInstruction(m_Target, EXIT);
			return *this;
		}
		inline VMWriter &ret()
		{
			VMResources::writeInstruction(m_Target, RET);
			//TODO TODO TODO return types?
			return *this;
		}
		inline VMWriter &dump()
		{
			VMResources::writeInstruction(m_Target, DUMP);
			return *this;
		}

		inline const std::vector<instruction_t> &getInstructions() const { return m_Target; }
		inline const std::vector<std::string> &getConstants() const { return m_Constants; }
		inline const int getLocals() const { return m_MaxLocals; }
		inline const int getStackHeight() const { return m_MaxStackHeight; }
	private:
		inline void stack(int amount) 
		{
			m_CurrentStackHeight += amount;
			if (m_CurrentStackHeight < 0) {
				ERROR("Stackheight < 0");
			}
			if (m_CurrentStackHeight > m_MaxStackHeight) {
				m_MaxStackHeight = m_CurrentStackHeight;
			}
		}
		inline void local(int l) {
			if (l < 0) {
				ERROR("Local < 0");
			}
			l += 1;
			if (l > m_MaxLocals) {
				m_MaxLocals = l;
			}
		}
		inline size_t constant(const std::string &c) {
			size_t index = 0;
			for (; index < m_Constants.size(); index++) {
				if (c == m_Constants[index])
					return index;
			}
			m_Constants.push_back(c);
			return index;
		}
	};
}