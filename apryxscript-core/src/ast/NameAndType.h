#pragma once

#include <string>

#include "NamedType.h"

namespace apryx {

	class NameAndType {
	public:
		std::string m_Name;

		std::shared_ptr<NamedType> m_Type;

		virtual std::string toString();
	};

}