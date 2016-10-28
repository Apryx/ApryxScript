#pragma once

#include "VMTypes.h"
#include <memory>

namespace apryx {
	struct VMObject;
	struct VMValue;

	typedef bool(*native_t)(std::vector<VMValue>&, int); //The stack, and the arguments, returning whether it succeeded or not

#pragma pack(push, 4)
	struct VMValue {
		union {
			//32 bit
			float_t m_Float;
			int_t m_Int;

			short_t m_Short;
			byte_t m_Byte;

			index_t m_Index;

			//64 bit
			double_t m_Double;
			long_t m_Long;
			native_t m_Native;

			byte_t b[16];

			//128 bit
			struct {
				long_t l1;
				long_t l2;
			} m_Raw;

			//Careful with this one.
			//10/10 i should do my own reference counting and not add a full shared ptr to this
			//But whatever, this thing is fucking 128bit
			std::shared_ptr<VMObject> m_VMObject;
		};

		enum class Type {
			VOID,
			INT,
			FLOAT,

			NATIVE_FUNCTION,
			FUNCTION,
			OBJECT
		};
	private:
		Type m_Type;

	public:
		VMValue();
		VMValue(const VMValue &);
		VMValue(VMValue &&);
		~VMValue();

		inline Type getType() const { return m_Type; }
		inline void setType(Type type)
		{
			//The question is, will this be enough?
			if (m_Type == Type::OBJECT)
				m_VMObject.reset();

			m_Type = type;
		}

		VMValue &operator=(const VMValue &);

		friend std::ostream &operator<<(std::ostream &o, const VMValue &value);
	};
#pragma pack(pop)

	typedef VMValue VMOperandSlot;

}