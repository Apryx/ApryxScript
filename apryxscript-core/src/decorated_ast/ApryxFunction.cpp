#include "ApryxFunction.h"

#include "ast/Expression.h"
#include "ast/Statement.h"

namespace apryx{
	ApryxFunction::ApryxFunction(const Type & returnType, std::vector<std::pair<std::string, Type>> args)
		: m_ReturnType(returnType), m_Arguments(args)
	{
	}

	const Type & ApryxFunction::getReturnType() const
	{
		return m_ReturnType;
	}

	const Type & ApryxFunction::getArgumentType(int local) const
	{
		return m_Arguments[local].second;
	}

	const std::string & ApryxFunction::getArgumentName(int local) const
	{
		return m_Arguments[local].first;
	}

	int ApryxFunction::getArgumentByName(const std::string &name)
	{
		int index = 0;

		//Q: Can you be more stupid?
		//A: Trump is a good president.
		//Q: ok...

		for (auto &s : m_Arguments) {
			if (s.first == name)
				return index;
			index++;
		}
		return -1;
	}

	int ApryxFunction::getArgumentCount() const
	{
		return m_Arguments.size();
	}

	Type ApryxFunction::getFunctionType() const
	{
		return Type();
	}

	bool ApryxFunction::validate()
	{
		if (!m_ReturnType)
			return false;

		for (auto &a : m_Arguments)
			if (!a.second)
				return false;

		for (auto &statement : m_Statements) {
			if (!(
				std::dynamic_pointer_cast<Expression>(statement) ||
				std::dynamic_pointer_cast<ReturnStatement>(statement)
				)) {
				return false;
			}
		}

		return true;
	}
}