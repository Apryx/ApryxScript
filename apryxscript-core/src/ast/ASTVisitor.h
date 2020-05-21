#pragma once

#include "Statement.h"
#include "Expression.h"

#include "logger/log.h"

namespace apryx {

	class ASTVisitor {
	public:
		virtual void visit(const Statement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const Expression &exp) { LOG("Unimplemented Statement."); };

		virtual void visit(const FunctionStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const VariableStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const BlockStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const StructureStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ReturnStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ExpressionStatement &exp) { LOG("Unimplemented Statement."); };

		virtual void visit(const NamespaceStatement &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const IncludeStatement &exp) { LOG("Unimplemented Statement."); };

		virtual void visit(const OperatorExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const PrefixOperatorExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const InvokeExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const ListExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const LookupExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const IdentiefierExpression &exp) { LOG("Unimplemented Statement."); };
		virtual void visit(const LiteralExpression &exp) { LOG("Unimplemented Statement."); };
	};
}