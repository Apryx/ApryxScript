#pragma once

#include <string>
#include <vector>
#include <memory>

namespace apryx {

	class ApryxFunction;

	class ApryxType {
	public:
		std::string m_Name;

		std::vector<std::shared_ptr<ApryxFunction>> m_Function;
	};
}