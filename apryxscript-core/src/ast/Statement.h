#pragma once

#include <string>
#include <memory>
#include <vector>

#include "decorated_ast/Decoration.h"
#include "lexer/Lexer.h"

#include "logger/log.h"

namespace apryx {

	//TODO fix painful use of shared_ptr
	//TODO fix painful use of toString() 
	//TODO fix constness for each statement type

	class StatementVisitor;

	class Expression;
	class Statement {
	protected:
		Statement() {};
		virtual ~Statement()  = default;
	public:
		Token m_Token;

		virtual std::string toString() = 0;
		virtual void accept(StatementVisitor &exp) = 0;
	};
	class Function : public Statement {
	public:
		std::string m_Name;
		std::string m_DeclaredReturnType;
		Type m_ReturnType; //TODO same as with variables, change this to something better (maybe even the decorated ast type system, because that just doesn't know stuff)
		std::shared_ptr<Expression> m_Arguments; //Can be a list expression, so yea (this is not the decorated ast yet remember)

		std::shared_ptr<Statement> m_Statement; //This can be a list (if its a block statement)

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class Variable : public Statement {
	public:
		std::string m_Name;
		std::string m_DeclaredType;
		Type m_Type; //Change this to a better type system with support for things other than strings

		std::shared_ptr<Expression> m_InitialValue;

		virtual std::string toString();
		bool isValid() { return m_DeclaredType.size() > 0 || m_InitialValue != nullptr; }
		bool hasDeclaredType() { return m_DeclaredType.size() > 0;}
		virtual void accept(StatementVisitor &exp);
	};
	class Block : public Statement {
	public:
		std::vector<std::shared_ptr<Statement>> m_Statements;

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class Structure : public Statement {
	public:
		std::string m_Name;
		std::string m_Parent;

		std::shared_ptr<Statement> m_Statement;

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class ReturnStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_ReturnExpression;

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class ExpressionStatement : public Statement {
	public:
		std::shared_ptr<Expression> m_Expression;

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	
	class Expression {
	protected:
		Expression() {}; //Why is this even here
	public:
		Decoration m_Decoration;
		Token m_Token;

		virtual std::string toString() = 0;
		virtual void accept(StatementVisitor &exp) = 0;
	};
	class OperatorExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Rhs;		//The right hand side
		std::string m_Operator;					//The actual operator

		OperatorExpression() = default;
		OperatorExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs, std::string op) : m_Operator(op), m_Rhs(rhs), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class PrefixOperatorExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Rhs;		//The left hand side
		std::string m_Operator;					//The actual operator

		PrefixOperatorExpression() = default;
		PrefixOperatorExpression(std::shared_ptr<Expression> rhs, std::string op) : m_Operator(op), m_Rhs(rhs) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class InvokeExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Args;		//The right hand side

		InvokeExpression() = default;
		InvokeExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> args) : m_Args(args), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class ListExpression : public Expression {
	public:
		std::vector<std::shared_ptr<Expression>> m_List;		//The left hand side

		ListExpression() = default;

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class LookupExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Rhs;		//The right hand side

		LookupExpression() = default;
		LookupExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) : m_Rhs(rhs), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class IdentiefierExpression : public Expression {
	public:
		std::string m_Identifier;

		IdentiefierExpression() = default;
		IdentiefierExpression(std::string id) : m_Identifier(id) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	class ConstantExpression : public Expression {
	public:
		std::string m_Constant;

		ConstantExpression() = default;
		ConstantExpression(std::string id) : m_Constant(id) {};

		virtual std::string toString();
		virtual void accept(StatementVisitor &exp);
	};
	
	class StatementVisitor {
	public:
		virtual void visit(const Statement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const Expression &exp) { LOG("Unimplemented Statement."); };

		virtual void visit(const Function &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const Variable &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const Block &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const Structure &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ReturnStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ExpressionStatement &exp) { LOG("Unimplemented Statement."); };

		virtual void visit(const OperatorExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const PrefixOperatorExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const InvokeExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ListExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const LookupExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const IdentiefierExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ConstantExpression &exp) { LOG("Unimplemented Statement."); };
	};



	//DEPRECTAED
	class Context : public Statement {
	public:
		virtual std::string toString();
		
		//TODO refactor this to a better place?
		//^^^ Is in progress with decorated AST, no worries past folkert :)
		virtual void performOperator(class VMWriter &, const std::string &op);			//TODO both types ofc
		virtual void performPrefixOperator(class VMWriter &, const std::string &op);		//TODO the one type ofc

		//nooo noo noo D:
		virtual void accept(StatementVisitor &exp) { exp.visit(*this); };
	};

	

}