#pragma once

#include "VMTypes.h"
#include "VMValue.h"

namespace apryx {
	struct VMObject {
		int_t refCount = 0;
		std::unordered_map<hash_t, VMValue> m_Objects;

		VMObject();
		~VMObject();
	};
}