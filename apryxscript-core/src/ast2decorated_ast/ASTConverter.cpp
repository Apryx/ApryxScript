#include "ASTConverter.h"

#include <sstream>

#include "ast/Statement.h"
#include "ast/Expression.h"
#include "decorated_ast/ApryxClass.h"

namespace apryx {

	void ASTConverter::process(std::shared_ptr<Block> block, ApryxEnvironment & env)
	{
		std::vector<std::shared_ptr<Structure>> structures;
		std::vector<std::shared_ptr<Function>> functions;

		std::vector<std::shared_ptr<Variable>> other;

		//Filter the order stuff
		for (auto statement : block->m_Statements) {
			if (auto function = std::dynamic_pointer_cast<Function>(statement)) {
				functions.push_back(function);
			}
			else if (auto structure = std::dynamic_pointer_cast<Structure>(statement)) {
				structures.push_back(structure);
			}
			else {
				LOG_ERROR("Can't convert " << statement->toString());
			}
		}

		// Maybe add some to be changed things
		// like function arguments that need to be changed
		// but maybe the class is declared later or something
		// i need to think about this

		//Parse classname first
		for (auto structure : structures) {
			ApryxClass cls;
			cls.m_Name = getNamespace() + structure->m_Name;
			
			env.addClass(cls.m_Name, cls);
		}

		//Then parse class outlines
		for (auto structure : structures) {
			auto *p = env.getApryxClass(getNamespace() + structure->m_Name);
			
			assert(p);
			processOutline(structure, *p);
		}

		//Parse function outlines
		for (auto structure : structures) {
			auto *p = env.getApryxClass(getNamespace() + structure->m_Name);

			assert(p);
			processOutline(structure, *p);
		}
	}

	void ASTConverter::processSequencial(std::shared_ptr<Block> block)
	{
		for (auto statement : block->m_Statements) {
			if (auto variable = std::dynamic_pointer_cast<Variable>(statement)) {

			}
			else if (auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(statement)) {

			}
		}
	}

	std::string ASTConverter::getNamespace() const
	{
		std::stringstream stream;

		for (auto &s : m_ScopeStack) {
			stream << s << "/";
		}

		return stream.str();
	}

	void ASTConverter::processOutline(std::shared_ptr<Function> structure, ApryxEnvironment & nmsp)
	{
	}

	void ASTConverter::processFull(std::shared_ptr<Function> block, ApryxEnvironment & nmsp)
	{
	}

	void ASTConverter::processOutline(std::shared_ptr<Structure> block, ApryxClass & nmsp)
	{

	}

	void ASTConverter::processFull(std::shared_ptr<Structure> block, ApryxClass & nmsp)
	{

	}

}
