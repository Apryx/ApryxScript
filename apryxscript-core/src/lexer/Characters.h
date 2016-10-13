#pragma once

#include <istream>
#include <memory>

namespace apryx {
	
	class Characters {
		std::shared_ptr<std::istream> m_Input;
		char m_Current;
	public:
		Characters(std::shared_ptr<std::istream> input);

		char current();
		char next();

		operator bool();
		bool operator!();
	};

}