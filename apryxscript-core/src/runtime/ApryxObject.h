#pragma once

#include <string>
#include <sstream>

namespace apryx {

	struct ApryxObject {
		std::string m_Data;
		ApryxObject(std::string data) : m_Data(data) {};

		virtual void assign(const ApryxObject &value);

		virtual std::string toString();
	};

	bool toFloat(const std::string &string, float &f);
	std::string toString(float f);

}