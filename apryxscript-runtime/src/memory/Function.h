#pragma once

#include "bytecode/ByteCode.h"

#include "Field.h"

namespace apryx {

	class Function {
		std::string m_Name;

		Type m_ReturnType;
		std::vector<Field> m_Parameters;

		ByteSequence m_Code;
	public:
		Function(std::string name, Type returnType, std::vector<Field> parameters, ByteSequence code);

		const std::string &name() const { return m_Name; };
		const Type &returnType() const { return m_ReturnType; };
		const std::vector<Field> &parameters() const { return m_Parameters; };
		const ByteSequence &code() const { return m_Code; };
		std::string signature() const;
	};

}