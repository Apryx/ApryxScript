#include "VMValue.h"
#include "logger/log.h"

namespace apryx {

	VMValue::VMValue()
		: m_VMObject(nullptr), m_Type(Type::VOID)
	{
	}

	VMValue::VMValue(const VMValue &other)
	{
		m_Type = other.m_Type;

		m_Raw.l1 = 0;
		m_Raw.l2 = 0;

		if (m_Type == Type::OBJECT) {
			m_VMObject = other.m_VMObject;
		}
		else {
			m_Raw = other.m_Raw;
		}
	}

	VMValue::VMValue(VMValue &&other)
		: m_Raw(std::move(other.m_Raw)), m_Type(std::move(other.m_Type))
	{

	}

	VMValue::~VMValue()
	{

	}

	VMValue &VMValue::operator=(const VMValue &other)
	{
		m_Type = other.m_Type;
		m_Raw.l1 = 0;
		m_Raw.l2 = 0;

		if (m_Type == Type::OBJECT) {
			m_VMObject = other.m_VMObject;
		}
		else {
			m_Raw = other.m_Raw;
		}

		return *this;
	}
}
