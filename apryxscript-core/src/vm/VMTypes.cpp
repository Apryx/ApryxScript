#include "VMTypes.h"
#include "VMValue.h"

#include <assert.h>
#include "logger/log.h"

namespace apryx {
	void verify_types()
	{
		assert(sizeof(instruction_t) == 1);
		assert(sizeof(index_t) == 4);
		assert(sizeof(float_t) == 4);
		assert(sizeof(short_t) == 2);
		assert(sizeof(byte_t) == 1);
		assert(sizeof(long_t) == 8);
		assert(sizeof(native_t) == 8);

		assert(sizeof(VMValue) == 20);
	}

}
