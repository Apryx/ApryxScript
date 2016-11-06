#pragma once

#include <map>
#include <vector>
#include <set>
#include <string>
#include <boost/optional.hpp>

#include <memory>

#include "Type.h"
#include "ApryxFunction.h"

namespace apryx {

	class ApryxClass;

	class ApryxNamespace {
		std::map<std::string, Type> m_Fields;

		std::map<std::string, std::vector<ApryxFunction>> m_Functions;
		std::map<std::string, ApryxClass> m_Classes;
	public:
		ApryxNamespace() {};
		virtual ~ApryxNamespace() {};

		boost::optional<Type> getFieldType(const std::string &name) const;
		boost::optional<Type> getFunctionType(const std::string &name) const;
		boost::optional<std::vector<Type>> getFunctionTypes(const std::string &name) const;

		bool getClassType(const std::string &name, Type &t) const;

		bool addField(const std::string &name, const Type &tp);
		bool addClass(const std::string &name, const ApryxClass &cls);
		bool addFunction(const std::string &name, const ApryxFunction &function);


		virtual bool validate();
	};

	class ApryxClass : public ApryxNamespace{
		std::map<std::string, Type> m_MemberFields;
		std::map<std::string, std::vector<Type>> m_MemberFunctions;

	public:
		ApryxClass() {};
		~ApryxClass() {};

		virtual bool validate() { return true; };
	};

	
}