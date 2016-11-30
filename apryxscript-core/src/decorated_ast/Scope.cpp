#include "Scope.h"

#include <sstream>

namespace apryx {

	ApryxNamespace *ApryxNamespace::createAnonymouseScope()
	{
		std::stringstream stream;
		stream << "$" << m_AnonymouseScopeCount;

		m_ChildScopes.push_back(
			std::make_unique<ApryxNamespace>(stream.str())
		);
		m_AnonymouseScopeCount++;

		return m_ChildScopes.back().get();
	}

	ApryxNamespace * ApryxNamespace::createScope(std::string name)
	{
		m_ChildScopes.push_back(
			std::make_unique<ApryxNamespace>(std::move(name))
		);

		return m_ChildScopes.back().get();
	}

}
