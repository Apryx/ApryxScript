#include "AST2XML.h"

#include <sstream>
#include <vector>

#include "ast/Statement.h"
#include "ast/Expression.h"

namespace apryx {

	static void open(std::ostream &stream, std::string name, std::vector<std::pair<std::string, std::string>> attributes)
	{
		stream << "<" << name << " ";
		
		for (auto &p : attributes) {
			stream << p.first << "=\"" << p.second << "\"";
		}

		stream << ">\n";
	}
	static void close(std::ostream &stream, std::string name)
	{
		stream << "</" << name << ">\n";
	}

	std::string convertToXML(Statement *statement)
	{
		std::stringstream stream;

		if (auto variable = dynamic_cast<VariableStatement*>(statement)) {
			open(stream, "variable", {
				// TODO fix the new XML output here
				//{"name", variable->m_Name},{"declaredType", variable->m_DeclaredType}
			});

			if (variable->m_InitialValue) {
				stream << convertToXML(variable->m_InitialValue.get());
			}

			close(stream, "variable");
		}
		else if (auto function = dynamic_cast<FunctionStatement*>(statement)) {
			open(stream, "function", {
				// TODO fix the actual XML output here
				//{ "name", function->m_Name },{ "returnType", function->m_DeclaredReturnType }
			});

			if (function->m_Statement) {
				stream << convertToXML(function->m_Statement.get());
			}

			close(stream, "function");
		}
		else if (auto structure = dynamic_cast<StructureStatement*>(statement)) {
			open(stream, "structure", {
				//{ "name", structure->m_Name },{ "extends", structure->m_Parent }
			});

			if (structure->m_Statement) {
				stream << convertToXML(structure->m_Statement.get());
			}

			close(stream, "structure");
		}
		else if (auto block = dynamic_cast<BlockStatement*>(statement)) {
			stream << convertToXML(block);
		}

		else if (auto returnStatement = dynamic_cast<ReturnStatement*>(statement)) {
			open(stream, "return", {});

			if (returnStatement->m_ReturnExpression) {
				stream << convertToXML(returnStatement->m_ReturnExpression.get());
			}

			close(stream, "return");
		}
		else if (auto expression = dynamic_cast<ExpressionStatement*>(statement)) {
			stream << convertToXML(expression->m_Expression.get());
		}

		return stream.str();
	}

	std::string convertToXML(BlockStatement *block)
	{
		std::stringstream stream;

		open(stream, "block", {});

		for (auto &s : block->m_Statements) {
			stream << convertToXML(s.get());
		}

		close(stream, "block");

		return stream.str();
	}

	std::string convertToXML(Expression *expression)
	{
		std::stringstream stream;

		if (auto constantExpression = dynamic_cast<LiteralExpression*>(expression)) {
			open(stream, "constant", {});

			stream << constantExpression->m_Value;

			close(stream, "constant");
		}

		return stream.str();
	}
}