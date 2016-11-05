#include "ASTConverter.h"

#include "ast/Statement.h"
#include "ast/Expression.h"
#include "decorated_ast/ApryxClass.h"

namespace apryx {

	void ASTConverter::process(std::shared_ptr<Statement> statement, ApryxNamespace & nmsp)
	{
		if (auto variable = std::dynamic_pointer_cast<Variable>(statement)) {

		}
		else if (auto function = std::dynamic_pointer_cast<Function>(statement)) {

		}
		else if (auto structure = std::dynamic_pointer_cast<Structure>(statement)) {

		}
		else if (auto expression = std::dynamic_pointer_cast<Expression>(statement)) {

		}
	}

}
