#pragma once

#include <string>

namespace apryx {
	class Statement;
	class Expression;
	class BlockStatement;

	std::string convertToXML(Statement *);
	std::string convertToXML(BlockStatement *);
	std::string convertToXML(Expression *);
}