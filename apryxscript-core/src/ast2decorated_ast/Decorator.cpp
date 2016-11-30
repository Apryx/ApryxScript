#include "Decorator.h"

#include "ast/Statement.h"
#include "ast/Expression.h"

namespace apryx {

	void Decorator::next()
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

	void Decorator::insert(std::shared_ptr<Statement> statement)
	{
		m_Statements.push(statement);
	}
	
	bool Decorator::hasNext()
	{
		return m_Statements.size() > 0;
	}

	void Decorator::visit(const Variable & exp)
	{

	}

	void Decorator::visit(const Block & exp)
	{
		for (auto& e : exp.m_Statements)
		{
			insert(e);
		}
	}

}
