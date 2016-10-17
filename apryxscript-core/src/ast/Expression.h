#pragma once

#include "Statement.h"
#include "lexer/Lexer.h"

#include <vector>

namespace apryx {
	
	class Expression : public Statement{
	protected:
		Expression() {}; //Why is this even here
	public:
		Token m_Token;

		virtual std::string toString() = 0;
	};

	class OperatorExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Rhs;		//The right hand side
		std::string m_Operator;					//The actual operator

		OperatorExpression() = default;
		OperatorExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> rhs, std::string op) : m_Operator(op), m_Rhs(rhs), m_Lhs(lhs) {};

		virtual std::string toString();
	};

	class InvokeExpression : public Expression {
	public:
		std::shared_ptr<Expression> m_Lhs;		//The left hand side
		std::shared_ptr<Expression> m_Args;		//The right hand side

		InvokeExpression() = default;
		InvokeExpression(std::shared_ptr<Expression> lhs, std::shared_ptr<Expression> args) : m_Args(args), m_Lhs(lhs) {};

		virtual std::string toString();
	};

	class ListExpression : public Expression {
	public:
		std::vector<std::shared_ptr<Expression>> m_Expressions;		//The left hand side

		ListExpression() = default;

		virtual std::string toString();
	};

	class IdentiefierExpression : public Expression {
	public:
		std::string m_Identifier;

		IdentiefierExpression() = default;
		IdentiefierExpression(std::string id) : m_Identifier(id) {};

		virtual std::string toString();
	};


	class ConstantExpression : public Expression {
	public:
		std::string m_Constant;
		enum Type{
			STRING, FLOAT, INT, DOUBLE, LONG
		} m_Type;

		ConstantExpression() = default;
		ConstantExpression(std::string id) : m_Constant(id) {};

		virtual std::string toString();
	};

}