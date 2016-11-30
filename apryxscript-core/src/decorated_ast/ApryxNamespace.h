#pragma once

#include <vector>
#include <boost/optional.hpp>

#include "Type.h"
#include "ApryxVariable.h"

namespace apryx {

	enum class ApryxNamespaceType {
		PACKAGE,
		CLASS,
		FUNCTION
	};

	class ApryxNamespace{
		std::vector<ApryxNamespace> m_ChildScopes;

		std::vector<ApryxVariable> m_Variables;
	
		std::string m_Name;

		ApryxNamespace *m_Parent;
		ApryxNamespaceType m_Type;

		int m_AnonymouseScopeCount = 0;
	public:
		ApryxNamespace(std::string name) : m_Name(std::move(name)) {};

		ApryxNamespace *createAnonymouseNamespace();
		ApryxNamespace *createNamespace(std::string name);

		bool addVariable(ApryxVariable variable);
		std::vector<ApryxVariable> getVariablesByName(const std::string &name, bool searchParent = true);

	
		void setParent(ApryxNamespace *nmsp) { m_Parent = nmsp; };
	};

}