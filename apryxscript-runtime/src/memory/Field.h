#pragma once

#include <string>
#include "Type.h"

namespace apryx {

	class Field {
		std::string m_Name;
		Type m_Type;
	public:
		Field();
		Field(std::string name, Type type);

		const std::string &name() const { return m_Name; };
		const Type &type() const { return m_Type; };
	};

}