#pragma once

#include <vector>
#include <memory>
#include <string>

namespace apryx {

	class ApryxFunction;
	class ApryxType;

	class ApryxNamespace {
	public:
		ApryxNamespace* m_Parent;

		std::string m_Name;

		std::vector<std::shared_ptr<ApryxFunction>> m_Functions;
		std::vector<std::shared_ptr<ApryxType>> m_Types;
	};
}