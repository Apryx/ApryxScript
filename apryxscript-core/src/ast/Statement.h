#pragma once

#include <string>
#include <memory>
#include <vector>

#include <boost/optional.hpp>

namespace apryx {

	//TODO fix painful use of shared_ptr
	//TODO fix painful use of toString() 
	//TODO fix constness for each statement type

	class Expression;

	class Statement {
	protected:
		Statement() {};
		virtual ~Statement()  = default;
	public:
		virtual std::string toString() = 0;
	};

	class Function : public Statement {
	public:
		std::string m_Name;
		Type m_ReturnType; //TODO same as with variables, change this to something better (maybe even the decorated ast type system, because that just doesn't know stuff)
		std::shared_ptr<Expression> m_Arguments; //Can be a list expression, so yea (this is not the decorated ast yet remember)

		std::shared_ptr<Statement> m_Statement; //This can be a list (if its a block statement)

		virtual std::string toString();
	};

	class Variable : public Statement {
	public:
		std::string m_Name;
		std::string m_Type; //Change this to a better type system with support for things other than strings

		std::shared_ptr<Expression> m_InitialValue;

		virtual std::string toString();
		bool isValid() { return m_Type.size() > 0 || m_InitialValue != nullptr; }
	};

	class Block : public Statement {
	public:
		std::vector<std::shared_ptr<Statement>> m_Statements;

		virtual std::string toString();
	};

	class Structure : public Statement {
	public:
		std::string m_Name;
		std::string m_Parent;

		std::shared_ptr<Statement> m_Statement;

		virtual std::string toString();
	};

	class ReturnStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_ReturnExpression;

		virtual std::string toString();
	};

	class ExpressionStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_Expression;

		virtual std::string toString();
	};

	//DEPRECTAED
	class Context : public Statement {
	public:
		virtual std::string toString();
		
		//TODO refactor this to a better place?
		//^^^ Is in progress with decorated AST, no worries past folkert :)
		virtual void performOperator(class VMWriter &, const std::string &op);			//TODO both types ofc
		virtual void performPrefixOperator(class VMWriter &, const std::string &op);		//TODO the one type ofc
	};

	

}