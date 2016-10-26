#pragma once

#include "VMTypes.h"
#include <vector>

namespace apryx {
	struct VMSlot {
		union {
			index_t index;

			float_t f;
			int_t i;
			short_t s[2];
			byte_t b[4];
		};
	};

	typedef std::vector<VMSlot> VMStack;
}