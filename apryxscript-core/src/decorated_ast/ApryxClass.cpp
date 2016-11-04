#include "ApryxClass.h"
#include "ApryxFunction.h"

namespace apryx {

	boost::optional<Type> ApryxNamespace::getFieldType(const std::string & name) const
	{
		auto i = m_Fields.find(name);

		if (i == m_Fields.end())
			return boost::none;

		return i->second;
	}

	boost::optional<Type> ApryxNamespace::getFunctionType(const std::string & name) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return boost::none;

		return i->second[0].getFunctionType();
	}

	boost::optional<std::vector<Type>> ApryxNamespace::getFunctionTypes(const std::string & name) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return false;

		std::vector<Type> v;

		for (auto &a : i->second)
			v.push_back(a.getFunctionType());

		return std::move(v);
	}

	bool ApryxNamespace::addField(const std::string & name, const Type & tp)
	{
		if (m_Fields.find(name) != m_Fields.end()) {
			return false;
		}

		m_Fields.insert(std::make_pair(name, tp));

		return true;
	}

	bool ApryxNamespace::validate()
	{
		return true;
	}

	
}
