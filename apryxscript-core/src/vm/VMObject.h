#pragma once

#include "VMTypes.h"
#include "VMValue.h"
#include <map>

namespace apryx {
	struct VMObject {
		int_t refCount = 0;

		//TODO change this to unordererd_map, and to hash_t, not string, for max speed!
		std::map<std::string, VMValue> m_Objects;

		VMObject();
		~VMObject();
	};
}