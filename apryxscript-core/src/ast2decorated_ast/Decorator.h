#pragma once

#include <memory>
#include <queue>

#include "ast/Statement.h"

namespace apryx { 

	class SemanticChecker : public StatementVisitor {

		//Semantic checker
		//
		//Create queue programQueue
		//Add all statements to programQueue
		//Mark all statements in programQueue with the globalScope
		//
		//Optional: Sort the list in order class -> function -> rest
		//
		//for each statement in programQueue
		//	if class -> Push content to programQueue, and mark every statement in the class
		//				with the scope they are in. Then register this class as an existing type.
		//	if func  -> Same as with class. Then register this function as an existing function
		//	if var   -> Check the expression, if the identifiers exist. Then register it as a known
		//				identifier.
		//	if exp	 -> Check if the identifiers exist (e.g. "cls.field", only check if cls exists, 
		//				field comes later in the type checker)
		//	if block -> Check everything in the block. Mark everything in the block as the **same**
		//				scope as the block itself.
		//
		//
		// Optional sanity check that all statements are marked with a scope

		std::queue<std::shared_ptr<Statement>>		m_Statements;

		int steps = 0;
	private:
		virtual void visit(const Function &exp) override;
		virtual void visit(const Variable &exp) override;
		virtual void visit(const Block &exp) override;
		virtual void visit(const Structure &exp) override {};
		virtual void visit(const ReturnStatement &exp) override {};
		virtual void visit(const ExpressionStatement &exp) override {};

		virtual void visit(const OperatorExpression &exp) override {};
		virtual void visit(const PrefixOperatorExpression &exp) override {};
		virtual void visit(const InvokeExpression &exp) override {};
		virtual void visit(const ListExpression &exp) override {};
		virtual void visit(const LookupExpression &exp) override {};
		virtual void visit(const IdentiefierExpression &exp) override {};
		virtual void visit(const ConstantExpression &exp) override {};


	public:
		void next();

		void insert(std::shared_ptr<Statement> statement);
	
		bool hasNext();
	};

}