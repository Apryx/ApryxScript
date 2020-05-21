#pragma once

#include "lexer/Lexer.h"

#include "Statement.h"

#include <vector>

//TODO refactor?

namespace apryx {

	class Expression {
	protected:
		Expression() {}; //Why is this even here
	public:
		Token m_Token;

		virtual std::string toString() = 0;
		virtual void accept(ASTVisitor &exp) = 0;
	};

	class OperatorExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Rhs;		//The right hand side
		std::string m_Operator;					//The actual operator

		OperatorExpression() = default;
		OperatorExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs, std::string op) : m_Operator(op), m_Rhs(rhs), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class PrefixOperatorExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Rhs;		//The left hand side
		std::string m_Operator;					//The actual operator

		PrefixOperatorExpression() = default;
		PrefixOperatorExpression(std::shared_ptr<Expression> rhs, std::string op) : m_Operator(op), m_Rhs(rhs) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class InvokeExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Args;		//The right hand side

		InvokeExpression() = default;
		InvokeExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> args) : m_Args(args), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class ListExpression : public Expression {
	public:
		std::vector<std::shared_ptr<Expression>> m_List;		//The left hand side

		ListExpression() = default;

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class LookupExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Rhs;		//The right hand side

		LookupExpression() = default;
		LookupExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs) : m_Rhs(rhs), m_Lhs(lhs) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class IdentiefierExpression : public Expression {
	public:
		std::string m_Identifier;

		IdentiefierExpression() = default;
		IdentiefierExpression(std::string id) : m_Identifier(id) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	class LiteralExpression : public Expression {
	public:
		enum {
			INTEGER,
			FLOAT,
			DOUBLE,
			STRING
		} m_Type;

		std::string m_Value;

		LiteralExpression() = default;
		LiteralExpression(std::string id) : m_Value(id) {};

		virtual std::string toString();
		virtual void accept(ASTVisitor &exp);
	};

	
}