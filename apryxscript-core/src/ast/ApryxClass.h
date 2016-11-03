#pragma once

#include <map>
#include <vector>
#include <set>
#include <string>

#include "Type.h"

namespace apryx {

	class Expression;

	class ApryxClass;
	class ApryxFunction;

	class ApryxNamespace {
		std::map<std::string, Type> m_Fields;

		std::map<std::string, std::set<Type>> m_Functions;
		std::map<std::string, ApryxClass> m_Classes;

	public:
		ApryxNamespace() {};
		virtual ~ApryxNamespace() {};

		bool getFieldType(const std::string &name, Type &t) const;
		bool getFunctionType(const std::string &name, Type &t) const;
		bool getFunctionTypes(const std::string &name, std::vector<Type> &t) const;

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

	class ApryxFunction {
	public: //Should be private
		Type m_ReturnType;
		std::vector<std::pair<std::string, Type>> m_Locals;
		int m_ArgumentCount;

		std::vector<Expression> m_Expressions;

	public:
		const Type &getReturnType() const;

		const Type &getLocalType(int local) const;
		const std::string &getLocalName(int local) const;

		int getLocalByName(const std::string &);

		int getArgumentCount() const;
		int getLocalCount() const;
	};

}