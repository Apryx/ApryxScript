#pragma once

#include "ast/Expression.h"
#include "vm/VMWriter.h"

namespace apryx {

	class ExpressionGenerator : public ExpressionVisitor {
	private:
		std::shared_ptr<Context> m_Context;
		VMWriter m_Writer;
	public:
		ExpressionGenerator(std::shared_ptr<Context> ctx);

		virtual void visit(const OperatorExpression &exp) override;
		virtual void visit(const PrefixOperatorExpression &exp) override;
		virtual void visit(const InvokeExpression &exp) override;
		virtual void visit(const ListExpression &exp) override;
		virtual void visit(const LookupExpression &exp) override;
		virtual void visit(const IdentiefierExpression &exp) override;
		virtual void visit(const ConstantExpression &exp) override;

		inline VMWriter &getWriter() { return m_Writer; }
	};
}