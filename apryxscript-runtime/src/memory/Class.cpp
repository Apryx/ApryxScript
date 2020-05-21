#include "Class.h"

namespace apryx {

	Class::Class(std::string name, std::vector<Field> fields, std::vector<FunctionStatement> functions)
		:m_Name(name), m_Fields(fields), m_Functions(functions)
	{ }

	int Class::getFunctionIndexBySignature(const std::string & name)
	{
		for (int i = 0; i < m_Functions.size(); i++)
			if (m_Functions[i].signature() == name)
				return i;

		return -1;
	}

	FunctionStatement & Class::getFunction(int index)
	{
		return m_Functions[index];
	}

	int Class::getFieldIndex(const std::string & name)
	{
		for (int i = 0; i < m_Fields.size(); i++)
			if (m_Fields[i].name() == name)
				return i;

		return -1;
	}

	Field & Class::getField(int index)
	{
		return m_Fields[index];
	}

}
