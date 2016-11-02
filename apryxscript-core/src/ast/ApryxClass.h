#pragma once

#include <map>
#include <vector>
#include <string>

#include "Type.h"

namespace apryx {

	class ApryxNamespace {
		std::map<std::string, Type> m_Fields;
		std::map<std::string, std::vector<Type>> m_Functions;

		ApryxNamespace() {};
		virtual ~ApryxNamespace() {};

		bool getFieldType(const std::string &name, Type &t) const;
		bool getFunctionType(const std::string &name, Type &t) const;
		bool getFunctionTypes(const std::string &name, std::vector<Type> &t) const;
	};

	class ApryxClass : public ApryxNamespace{
		std::map<std::string, Type> m_MemberFields;
		std::map<std::string, std::vector<Type>> m_MemberFunctions;

	public:
		ApryxClass();
		~ApryxClass();

		bool validate();
	};

}