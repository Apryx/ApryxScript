#include "ASTConverter.h"

#include "ast/Statement.h"
#include "ast/Expression.h"
#include "decorated_ast/ApryxClass.h"

namespace apryx {

	void ASTConverter::process(std::shared_ptr<Block> statement, ApryxEnvironment & env)
	{
		std::vector<std::shared_ptr<Structure>> structures;
		std::vector<std::shared_ptr<Function>> functions;

		std::vector<std::shared_ptr<Variable>> other;

		//Filter the order stuff
		for (auto a : statement->m_Statements) {
			if (auto function = std::dynamic_pointer_cast<Function>(statement)) {
				functions.push_back(function);
			}
			else if (auto structure = std::dynamic_pointer_cast<Structure>(statement)) {
				structures.push_back(structure);
			}
			else {
				LOG_ERROR("Can't convert " << a->toString());
			}
		}

		// Maybe add some to be changed things
		// like function arguments that need to be changed
		// but maybe the class is declared later or something
		// i need to think about this

		for (auto structure : structures) {
			ApryxClass cls;
			cls.m_Name = structure->m_Name;
			
			env.addClass(structure->m_Name, cls);
		}
		for (auto function : functions) {
			//ApryxFunction()
			ApryxFunction func(
				function->m_ReturnType,
				{}
				);

			env.addFunction(function->m_Name, func);
		}
	}

}
