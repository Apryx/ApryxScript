#include "Statement.h"
#include "Expression.h"
#include <sstream>

#include "vm/VMWriter.h"

#include "ASTVisitor.h"

namespace apryx {

	std::string VariableStatement::toString()
	{
		std::stringstream stream;

		stream << "var ";
		
		stream << m_NameAndType->toString();

		stream << ";";

		return stream.str();
	}

	void VariableStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

	
	std::string BlockStatement::toString()
	{
		std::stringstream stream;

		stream << "{";
		for (auto &a : m_Statements)
			stream << a->toString();
		stream << "}";

		return stream.str();
	}
	void BlockStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}
	std::string ReturnStatement::toString()
	{
		std::stringstream stream;

		stream << "return ";
		stream << m_ReturnExpression->toString();
		stream << ";";

		return stream.str();
	}
	
	void ReturnStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

	std::string FunctionStatement::toString()
	{
		std::stringstream stream;

		stream << "function ";
		stream << m_Name;
		stream << "(";

		for (int i = 0; i < m_Parameters.size(); i++) {
			
			stream << m_Parameters[i]->toString();

			if (i != m_Parameters.size() - 1) {
				stream << ", ";
			}
		}

		stream << ")";
		
		if (m_ReturnType) {
			stream << " : ";
			stream << m_ReturnType->toString();
		}
		stream << m_Statement->toString();

		return stream.str();
	}
	void FunctionStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}


	std::string ExpressionStatement::toString()
	{
		std::stringstream stream;

		stream << m_Expression->toString();
		stream << ";";

		return stream.str();
	}

	void ExpressionStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

	std::string StructureStatement::toString()
	{
		std::stringstream stream;

		if (m_Type == REFERENCE) {
			stream << "class ";
		}
		else {
			stream << "struct ";
		}

		stream << m_Name->toString();

		if (m_Parent) {
			stream << " extends ";
			stream << m_Parent->toString();
		}

		stream << m_Statement->toString();

		return stream.str();
	}

	void StructureStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}


	std::string CompilationUnit::toString()
	{
		std::stringstream stream;

		for (auto &a : m_Statements)
			stream << a->toString();

		return stream.str();
	}

	void CompilationUnit::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

	std::string NamespaceStatement::toString()
	{
		std::stringstream stream;

		stream << "namespace " << m_Name->toString() << ";";

		return stream.str();
	}

	void NamespaceStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

	std::string IncludeStatement::toString()
	{
		std::stringstream stream;

		stream << "include \"" << m_File << "\";";

		return stream.str();
	}

	void IncludeStatement::accept(ASTVisitor & exp)
	{
		exp.visit(*this);
	}

}
