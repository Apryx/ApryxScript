#pragma once

#include <string>
#include <memory>
#include <vector>

#include "NameAndType.h"
#include "NamedType.h"

namespace apryx {

	//TODO fix painful use of shared_ptr
	//TODO fix painful use of toString() 
	//TODO fix constness for each statement type

	class ASTVisitor;
	class Expression;
	
	// ========================================= //
	// Statements
	// ========================================= //
	class Statement {
	protected:
		Statement() {};
		virtual ~Statement()  = default;
	public:
		//Token m_Token;

		virtual std::string toString() = 0;
		virtual void accept(ASTVisitor &exp) = 0;
	};

	class FunctionStatement : public Statement {
	public:
		std::string m_Name;

		std::shared_ptr<NamedType> m_ReturnType;

		// TODO implement these
		std::vector<std::shared_ptr<NameAndType>> m_Parameters;

		std::shared_ptr<Statement> m_Statement; //This can be a list (if its a block statement)

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class VariableStatement : public Statement {
	public:
		// Maybe name and type and initial value?
		// Function arguments could use that too
		std::shared_ptr<NameAndType> m_NameAndType;

		std::shared_ptr<Expression> m_InitialValue;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};
	
	class BlockStatement : public Statement {
	public:
		std::vector<std::shared_ptr<Statement>> m_Statements;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};
	
	class StructureStatement : public Statement {
	public:
		std::shared_ptr<NamedType> m_Name; // TODO make this TypeName
		std::shared_ptr<NamedType> m_Parent;

		std::shared_ptr<Statement> m_Statement;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
		
		enum {
			REFERENCE,
			VALUE
		} m_Type;
	};
	
	class NamespaceStatement : public Statement {
	public:
		std::shared_ptr<NamedType> m_Name; // TODO make this TypeName

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class IncludeStatement : public Statement {
	public:
		std::string m_File;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};


	class CompilationUnit : public Statement{
	public:
		std::vector<std::shared_ptr<Statement>> m_Statements;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class ReturnStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_ReturnExpression;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};
	
	class ExpressionStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_Expression;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

}