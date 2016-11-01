#include "Generator.h"

namespace apryx {
	ExpressionGenerator::ExpressionGenerator(std::shared_ptr<Context> ctx)
		: m_Context(ctx)
	{

	}
	void ExpressionGenerator::visit(const OperatorExpression & exp)
	{
		exp.m_Lhs->accept(*this);
		exp.m_Rhs->accept(*this);
		
		m_Context->performOperator(m_Writer, exp.m_Operator);
	}

	void ExpressionGenerator::visit(const PrefixOperatorExpression & exp)
	{
	}

	void ExpressionGenerator::visit(const InvokeExpression & exp)
	{
		int argCount = 0;
		if (exp.m_Args) {

			//Push arguments onto the stack
			exp.m_Args->accept(*this);

			auto v = std::dynamic_pointer_cast<ListExpression>(exp.m_Args);
			if (v) {
				argCount = v->m_List.size();
			}
			else {
				argCount = 1;
			}
		}

		//push function ref onto the stack
		exp.m_Lhs->accept(*this);

		//Invoke the function!
		m_Writer.invoke(argCount);
	}

	void ExpressionGenerator::visit(const ListExpression & exp)
	{
		for (auto a : exp.m_List) {
			a->accept(*this);
		}
	}

	void ExpressionGenerator::visit(const LookupExpression & exp)
	{
		//TODO todo todo
	}

	void ExpressionGenerator::visit(const IdentiefierExpression & exp)
	{
		m_Writer.pushglobal();
		m_Writer.getfield(exp.m_Identifier);
	}

	void ExpressionGenerator::visit(const ConstantExpression & exp)
	{
		switch (exp.m_Type) {
		case ConstantExpression::Type::FLOAT:
			m_Writer.push(std::stof(exp.m_Constant));
			break;
		case ConstantExpression::Type::INT:
			m_Writer.push(std::stoi(exp.m_Constant));
			break;
		}
	}
}
