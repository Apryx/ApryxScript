#pragma once

#include <string>
#include <memory>

#include "ApryxType.h"

namespace apryx {

	class ApryxVariable {
		std::string m_Name;

		std::shared_ptr<ApryxType> m_Type;
	};

}