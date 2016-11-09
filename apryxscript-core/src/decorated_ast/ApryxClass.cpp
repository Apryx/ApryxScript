#include "ApryxClass.h"
#include "ApryxFunction.h"

namespace apryx {

	boost::optional<Type> ApryxEnvironment::getFieldType(const std::string & name) const
	{
		auto i = m_Fields.find(name);

		if (i == m_Fields.end())
			return boost::none;

		return i->second;
	}

	boost::optional<Type> ApryxEnvironment::getFunctionType(const std::string & name) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return boost::none;

		return i->second[0].getFunctionType();
	}

	boost::optional<std::vector<Type>> ApryxEnvironment::getFunctionTypes(const std::string & name) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return boost::none;

		std::vector<Type> v;

		for (auto &a : i->second)
			v.push_back(a.getFunctionType());

		return std::move(v);
	}

	ApryxClass * ApryxEnvironment::getApryxClass(const std::string & name)
	{
		auto i = m_Classes.find(name);
		if (i == m_Classes.end()) {
			return nullptr;
		}

		return &i->second;
	}

	bool ApryxEnvironment::addField(const std::string & name, const Type & tp)
	{
		if (m_Fields.find(name) != m_Fields.end()) {
			return false;
		}

		m_Fields.insert(std::make_pair(name, tp));

		return true;
	}

	bool ApryxEnvironment::addClass(const std::string & name, const ApryxClass & cls)
	{
		return false;
	}

	bool ApryxEnvironment::validate()
	{
		return true;
	}

	
}
