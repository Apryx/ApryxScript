#include "ApryxClass.h"

namespace apryx {
	bool ApryxClass::validate()
	{
		return true;
	}

	bool ApryxNamespace::getFieldType(const std::string & name, Type & t) const
	{
		auto i = m_Fields.find(name);
		if (i == m_Fields.end())
			return false;

		t = i->second;

		return true;
	}

	bool ApryxNamespace::getFunctionType(const std::string & name, Type & t) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return false;

		t = i->second[0];

		return true;
	}

	bool ApryxNamespace::getFunctionTypes(const std::string & name, std::vector<Type>& t) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return false;

		t = i->second;

		return true;
	}
}
