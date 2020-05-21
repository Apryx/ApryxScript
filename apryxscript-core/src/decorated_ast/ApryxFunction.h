#pragma once

#include <string>

#include <memory>
#include <vector>

#include "AccessModifier.h"
#include "ApryxVariable.h"

namespace apryx {

	class ApryxType;
	class ApryxFunction;

	class ApryxFunction {
	public:
		std::string m_Name;

		AccessModifier m_Modifiers;
		bool m_Static;

		std::vector<std::shared_ptr<ApryxVariable>> m_Parameters;
	};

}