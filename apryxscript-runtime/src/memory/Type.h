#pragma once

#include <string>

namespace apryx {

	class Type {
	public:
		enum Native{
			Void = 0,
			Byte,
			Short,
			Int,
			Long,
			Boolean,
			Float,
			Double,
			Pointer
		};
	private:
		std::string m_Name;
		Native m_Type;

	public:
		Type();
		Type(Native type);
		Type(std::string typeName);

		Native getNative() const;
		std::string getTypeName() const;

		size_t size() const;
	};

}