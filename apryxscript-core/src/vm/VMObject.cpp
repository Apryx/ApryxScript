#include "VMObject.h"
#include "logger/log.h"

namespace apryx {
	void VMObject::set(const std::string &s, const VMValue &v)
	{
		m_Objects[s] = v;
	}
	VMValue VMObject::get(const std::string &s)
	{
		return m_Objects.at(s);
	}
	VMObject::VMObject()
	{
	}
	VMObject::~VMObject()
	{
	}
	std::ostream & operator<<(std::ostream & o, const VMObject & obj)
	{
		o << "{";

		for (auto &a : obj.m_Objects) {
			o << a.first << " = " << a.second << ",";
		}

		o << "}";

		return o;
	}
}
