#pragma once

#include <vector>
#include <memory>

namespace apryx {

	class ApryxNamespace{
		std::vector<std::unique_ptr<ApryxNamespace>> m_ChildScopes;
	
		std::string m_Name;

		int m_AnonymouseScopeCount = 0;
	public:
		ApryxNamespace(std::string name) : m_Name(std::move(name)) {};

		ApryxNamespace *createAnonymouseScope();
		ApryxNamespace *createScope(std::string name);
	};

}