#pragma once

#include <string>

namespace apryx {
	class Statement;
	class Expression;
	class Block;

	std::string convertToXML(Statement *);
	std::string convertToXML(Block *);
	std::string convertToXML(Expression *);
}