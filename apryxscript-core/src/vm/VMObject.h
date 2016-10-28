#pragma once

#include "VMTypes.h"
#include "VMValue.h"
#include <map>

namespace apryx {
	struct VMObject {
		//TODO change this to unordererd_map, and to hash_t, not string, for max speed!
		std::map<std::string, VMValue> m_Objects;

		void set(const std::string &, const VMValue &);
		VMValue get(const std::string &);

		VMObject();
		~VMObject();

		friend std::ostream &operator<<(std::ostream &o, const VMObject &obj);
	};
}