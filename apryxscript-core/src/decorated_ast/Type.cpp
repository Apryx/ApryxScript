#include "Type.h"

#include <sstream>
#include <assert.h>

namespace apryx {
	
	Type::Type()
	{
		m_Type = ERROR;
	}

	Type::~Type()
	{

	}
	
	bool Type::isBuildIn() const
	{
		return m_Type == BUILD_IN;
	}

	bool Type::isClass() const
	{
		return m_Type == CLASS;
	}
	
	bool Type::isFunction() const
	{
		return m_Type == FUNCTION;
	}
	
	std::string Type::getSignature() const
	{
		std::stringstream stream;

		if (isClass()) {
			stream << "L";				//L for classes
			stream << m_Name;
			stream << ";";
		}

		else if (isFunction()) {
			stream << "R";				//R for functions :')
			stream << m_Name;

			stream << "(";
			for (int i = 0; i < getArgumentCount(); i++){
				stream << getArgumentType(i).getSignature();
			}
			stream << ")";
			stream << getReturnType().getSignature();
		}
		else if(isBuildIn()){
			stream << m_Name;
		}

		return stream.str();
	}

	const std::string &Type::getName() const
	{
		assert(isClass());
		return m_Name;
	}

	int Type::getArgumentCount() const
	{
		assert(isFunction());
		return m_Signatures.size() - 1;
	}
	const Type & Type::getArgumentType(int index) const
	{
		assert(isFunction());
		return m_Signatures[index + 1];
	}
	const Type & Type::getReturnType() const
	{
		assert(isFunction());
		return m_Signatures[0];
	}

	Type Type::getInt()
	{
		Type type;
		type.m_Type = BUILD_IN;
		
		type.m_Name = "I";
		return type;
	}

	Type Type::getFloat()
	{
		Type type;
		type.m_Type = BUILD_IN;

		type.m_Name = "F";
		return type;
	}

	Type Type::getDouble()
	{
		Type type;
		type.m_Type = BUILD_IN;

		type.m_Name = "D";
		return type;
	}

	Type Type::getString()
	{
		Type type;
		type.m_Type = CLASS;

		type.m_Name = "apryx/lang/String";

		return type;
	}

	Type Type::getVoid()
	{
		Type type;
		type.m_Type = BUILD_IN;

		type.m_Name = "V";
		return type;
	}

	Type Type::getClass(const std::string cls)
	{
		Type type;
		type.m_Type = CLASS;

		type.m_Name = cls;

		return type;
	}

	Type::operator bool()
	{
		return m_Type != ERROR;
	}

	bool operator==(const Type & left, const Type & right)
	{
		if (left.m_Type != right.m_Type)
			return false;
		
		if (left.m_Type == Type::BUILD_IN)
			return left.m_Name == right.m_Name;

		if (left.m_Type == Type::FUNCTION) 
			return left.m_Signatures == right.m_Signatures;
		
		if (left.m_Type == Type::CLASS)
			return left.m_Name == right.m_Name;

		return false;
	}

	std::ostream& operator<<(std::ostream &o, const Type &type)
	{
		return o << type.getSignature();
	}
}
