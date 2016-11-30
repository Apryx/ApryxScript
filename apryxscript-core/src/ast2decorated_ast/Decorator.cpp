#include "Decorator.h"

#include "ast/Statement.h"
#include "ast/Expression.h"

namespace apryx {

	void SemanticChecker::next()
	{
		if (!hasNext())
			return;

		steps++;

		//First try to process the statements
		if (m_Statements.size() > 0) {
			auto p = m_Statements.front();
			m_Statements.pop();

			p->accept(*this);
		}

	}

	void SemanticChecker::insert(std::shared_ptr<Statement> statement)
	{
		m_Statements.push(statement);
	}
	
	bool SemanticChecker::hasNext()
	{
		return m_Statements.size() > 0;
	}

	void SemanticChecker::visit(const Function & exp)
	{

	}

	void SemanticChecker::visit(const Variable & exp)
	{

	}

	void SemanticChecker::visit(const Block & exp)
	{
		for (auto& e : exp.m_Statements)
		{
			insert(e);
		}
	}

}
