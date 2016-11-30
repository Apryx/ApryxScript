#include "ApryxNamespace.h"

#include <sstream>

namespace apryx {

	ApryxNamespace *ApryxNamespace::createAnonymouseNamespace()
	{
		std::stringstream stream;
		stream << "$" << m_AnonymouseScopeCount;

		m_ChildScopes.push_back(
			ApryxNamespace(stream.str())
		);
		m_ChildScopes.back().setParent(this);

		m_AnonymouseScopeCount++;

		return &m_ChildScopes.back();
	}

	ApryxNamespace * ApryxNamespace::createNamespace(std::string name)
	{
		m_ChildScopes.push_back(
			ApryxNamespace(std::move(name))
		);
		m_ChildScopes.back().setParent(this);

		return &m_ChildScopes.back();
	}

	bool ApryxNamespace::addVariable(ApryxVariable variable)
	{

	}

	std::vector<ApryxVariable> ApryxNamespace::getVariablesByName(const std::string & name, bool searchParent)
	{
		std::vector<ApryxVariable> variables;



		return std::move(variables);
	}

}
