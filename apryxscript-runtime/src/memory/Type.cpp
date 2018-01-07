#include "Type.h"

#include <sstream>

namespace apryx {
	Type::Type()
		: m_Type(Native::Void)
	{ }

	Type::Type(Native type)
		: m_Name(""), m_Type(type)
	{ }

	Type::Type(std::string typeName)
		: m_Name(typeName), m_Type(Native::Pointer)
	{ }

	Type::Native Type::getNative() const
	{
		return m_Type;
	}

	std::string Type::getTypeName() const
	{
		switch (m_Type)
		{
		case Void:
			return "V";
		case Byte:
			return "B";
		case Short:
			return "S";
		case Int:
			return "I";
		case Long:
			return "L";

		case Float:
			return "F";
		case Double:
			return "D";

		case Boolean:
			return "Z";

		case Pointer:
		{
			std::stringstream string;
			string << "Z" << m_Name << ";";
			return string.str();
		}
		default:
			throw "Invalid type on getting typename";
		}
	}

	size_t Type::size() const
	{
		switch (m_Type)
		{
		case Void:
			return 0;
		case Byte:
			return sizeof(int8_t);
		case Short:
			return sizeof(int16_t);
		case Int:
			return sizeof(int32_t);
		case Long:
			return sizeof(int64_t);

		case Float:
			return sizeof(float);
		case Double:
			return sizeof(double);

		case Boolean:
			return sizeof(int8_t);

		case Pointer:
			return sizeof(void*);
		default:
			throw "Invalid type on getting typename";
		}
	}
}
