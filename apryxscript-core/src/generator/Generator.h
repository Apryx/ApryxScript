#pragma once

#include "ast/ASTVisitor.h"
#include "vm/VMWriter.h"

namespace apryx {

	class Context : public Statement {
	public:
		virtual std::string toString();
		
		//TODO refactor this to a better place?
		//^^^ Is in progress with decorated AST, no worries past folkert :)
		virtual void performOperator(class VMWriter &, const std::string &op);			//TODO both types ofc
		virtual void performPrefixOperator(class VMWriter &, const std::string &op);		//TODO the one type ofc

		//nooo noo noo D:
		virtual void accept(ASTVisitor &exp) { exp.visit(*this); };
	};

	class ExpressionGenerator : public ASTVisitor {
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
		virtual void visit(const LiteralExpression &exp) override;

		inline VMWriter &getWriter() { return m_Writer; }
	};
}