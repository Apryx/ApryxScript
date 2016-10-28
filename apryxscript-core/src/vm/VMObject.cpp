#include "VMObject.h"
#include "logger/log.h"

namespace apryx {
	VMObject::VMObject()
	{
		LOG("Created!");
	}
	VMObject::~VMObject()
	{
		LOG("Deleted.");
	}
}
