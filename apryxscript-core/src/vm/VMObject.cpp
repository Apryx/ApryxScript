#include "VMObject.h"
#include "logger/log.h"

namespace apryx {
	VMObject::VMObject()
	{
		LOG("create");
	}
	VMObject::~VMObject()
	{
		LOG("destroy");
	}
}
