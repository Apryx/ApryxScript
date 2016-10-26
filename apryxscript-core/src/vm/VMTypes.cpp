#include "VMTypes.h"

#include <assert.h>

namespace apryx {
	void verify_types()
	{
		assert(sizeof(instruction_t) * CHAR_BIT == 8);
		assert(sizeof(index_t) * CHAR_BIT == 32);
		assert(sizeof(float_t) * CHAR_BIT == 32);
		assert(sizeof(short_t) * CHAR_BIT == 16);
		assert(sizeof(byte_t) * CHAR_BIT == 8);
	}
}
