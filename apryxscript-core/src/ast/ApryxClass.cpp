#include "ApryxClass.h"

namespace apryx {

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

		//i->second[0];

		return true;
	}

	bool ApryxNamespace::getFunctionTypes(const std::string & name, std::vector<Type>& t) const
	{
		auto i = m_Functions.find(name);
		if (i == m_Functions.end())
			return false;

		//t = i->second;

		return true;
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
		return false;
	}
	const Type & ApryxFunction::getReturnType() const
	{
		return m_ReturnType;
	}

	const Type & ApryxFunction::getLocalType(int local) const
	{
		return m_Locals[local].second;
	}

	const std::string & ApryxFunction::getLocalName(int local) const
	{
		return m_Locals[local].first;
	}

	int ApryxFunction::getLocalByName(const std::string &name)
	{
		for (int i = 0; i < m_Locals.size(); i++) {
			if (m_Locals[i].first == name)
				return i;
		}
		return -1;
	}

	int ApryxFunction::getArgumentCount() const
	{
		return m_ArgumentCount;
	}

	int ApryxFunction::getLocalCount() const
	{
		return m_Locals.size();
	}
}
