#pragma once

#include <string>

namespace apryx {

	class NamedType {
	public:
		// TODO this can also have things like the namespace and stuff, but doesn't need it
		std::string m_Name;

		virtual std::string toString();
	};

}