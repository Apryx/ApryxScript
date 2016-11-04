#pragma once

#include "Type.h"
#include <vector>
#include <memory>

namespace apryx {

	class Statement;

	class ApryxFunction {
	public: //Should be private
		Type m_ReturnType;
		std::vector<std::pair<std::string, Type>> m_Arguments;

		//Possibly change this to unique_ptr?
		std::vector<std::shared_ptr<Statement>> m_Statements;

	public:
		ApryxFunction(const Type &returnType, std::vector<std::pair<std::string, Type>> args);

		const Type &getReturnType() const;

		const Type &getArgumentType(int local) const;
		const std::string &getArgumentName(int local) const;

		int getArgumentByName(const std::string &);

		int getArgumentCount() const;

		Type getFunctionType() const;

		bool validate();
	};

}