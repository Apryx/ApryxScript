#include "Field.h"

namespace apryx {
	Field::Field()
		: m_Name("undefined"), m_Type()
	{ }

	Field::Field(std::string name, Type type)
		: m_Name(name), m_Type(type)
	{ }
}
