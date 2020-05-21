#pragma once

#include <string>
#include "AccessModifier.h"

#include <memory>
#include <vector>

namespace apryx {

	class ApryxType;
	class ApryxFunction;

	class ApryxNamespace {
		std::string m_Name; // Root namespace is empty
	};

	class ApryxType {
		std::string m_Name;

		std::vector<std::shared_ptr<ApryxFunction>> m_Function;
	};

	class ApryxFunction {
		// Name might be empty in an annonymous function maybe who knows this is in progress
		std::string m_Name;

		AccessModifier m_Access;
		bool m_Static;

		std::vector<std::shared_ptr<ApryxType>> m_Parameters;
	};

}