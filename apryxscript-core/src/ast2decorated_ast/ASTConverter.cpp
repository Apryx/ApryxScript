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

		std::vector<std::shared_ptr<Statement>> other;

		//Filter the order stuff
		for (auto statement : block->m_Statements) {
			if (auto function = std::dynamic_pointer_cast<Function>(statement)) {
				functions.push_back(function);
			}
			else if (auto structure = std::dynamic_pointer_cast<Structure>(statement)) {
				structures.push_back(structure);
			}
			else {
				other.push_back(statement);
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
	}

	void ASTConverter::processSequencial(std::shared_ptr<Block> block, LocalsTable &table)
	{
		//TODO better error handling
		//Push a new block of locals
		table.push();

		for (auto statement : block->m_Statements) {
			if (auto variable = std::dynamic_pointer_cast<Variable>(statement)) {
				
				//Deduced type
				if (variable->m_InitialValue) {

					//Typecheck the initial value
					processSequencial(variable->m_InitialValue, table);

					//Check if the new value is even valid
					if (!(variable->m_InitialValue->m_Decoration.m_Type)) {
						LOG_ERROR("Unkown type for " << variable->m_Name);
						continue;
					}

					//Check whether the declared type is the actual same type
					if (variable->hasDeclaredType()) {
						auto t = table.getTypeByName(variable->m_DeclaredType);

						if (!t)
							LOG_ERROR("Incorrect type for variable");

						if (!(*t == variable->m_InitialValue->m_Decoration.m_Type)) {
							LOG_ERROR("Inconsistent variable types ");
						}
					}
					
					//Insert the variable, and check if it already exists
					if (!table.setTypeOf(variable->m_Name, variable->m_InitialValue->m_Decoration.m_Type)) {
						LOG_ERROR("Duplicate variable " << variable->m_Name);
					}
				}

				//Declared type
				else if(variable->hasDeclaredType()) {
					auto typeOpt = table.getTypeByName(variable->m_DeclaredType);

					if (!typeOpt) {
						LOG_ERROR("Unkown type " << variable->m_DeclaredType);
						continue;
					}
					
					if (!table.setTypeOf(variable->m_Name, *typeOpt)) {
						LOG_ERROR("Duplicate variable " << variable->m_Name);
					}
				}

				//No type?!?
				else {
					LOG_ERROR("Invalid variable");
				}
			}
			
			else if (auto expressionStatement = std::dynamic_pointer_cast<ExpressionStatement>(statement)) {
				processSequencial(expressionStatement->m_Expression, table);
			}
			else if (auto blockStatement = std::dynamic_pointer_cast<Block>(statement)) {
				processSequencial(blockStatement, table);
			}
			else {
				LOG_WARNING("Unchecked " << statement->toString());
			}
		}

		table.dump();

		//Pop the block of locals
		table.pop();
	}

	void ASTConverter::processSequencial(std::shared_ptr<Expression> exp, LocalsTable &table)
	{
		if (auto identifierExpression = std::dynamic_pointer_cast<IdentiefierExpression>(exp)) {
			auto typeOpt = table.getTypeOf(identifierExpression->m_Identifier);

			if (typeOpt) {
				identifierExpression->m_Decoration.m_Type = *typeOpt;
			}
			else {
				LOG_ERROR("Unkown type for identifier " << exp->toString());
			}
		}
		else if (auto constantExpression = std::dynamic_pointer_cast<ConstantExpression>(exp)) {
			return;
		}
		else {
			LOG_WARNING("Unchecked expression " << exp->toString());
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

	void ASTConverter::processOutline(std::shared_ptr<Structure> structure, ApryxClass & cls)
	{
		assert(cls.m_Name == structure->m_Name);

		//List of statements
		std::vector<std::shared_ptr<Statement>> statements;

		//Get the list of statements (either one, or a block)
		{
			auto block = std::dynamic_pointer_cast<Block>(structure->m_Statement);
			if (block) {
				statements = block->m_Statements;
			}
			else {
				statements.push_back(structure->m_Statement);
			}
		}
		
		//Use all these here!
		for (auto &i : statements) {
			if (auto function = std::dynamic_pointer_cast<Function>(i)) {

			}
			else if (auto variable = std::dynamic_pointer_cast<Variable>(i)) {
				
			}
			else {
				LOG_ERROR("Cant parse statement \"" << i << "\" in class body");
			}
		}
	}

	void ASTConverter::processFull(std::shared_ptr<Structure> block, ApryxClass & nmsp)
	{

	}

	boost::optional<Type> LocalsTable::getTypeOf(const std::string & name)
	{
		for (auto i = m_Symbols.rbegin(); i != m_Symbols.rend(); i++) {
			auto f = i->find(name);
			if (f != i->end()) {
				return f->second;
			}
		}

		return boost::none;
	}

	bool LocalsTable::setTypeOf(const std::string & name, const Type & type)
	{
		auto i = m_Symbols.back().find(name);
		
		if (i != m_Symbols.back().end())
			return false;

		m_Symbols.back().insert(std::make_pair(name, type));
		return true;
	}

	boost::optional<Type> LocalsTable::getTypeByName(const std::string & name)
	{
		if (name == "int")
			return Type::getInt();
		else if (name == "float")
			return Type::getFloat();
		else if (name == "void")
			return Type::getVoid();
		else
			return boost::none;
	}

	void LocalsTable::dump()
	{
		for (int i = 0; i < m_Symbols.size(); i++) {
			LOG("{");
			for (auto j = m_Symbols[i].begin(); j != m_Symbols[i].end(); j++) {
				LOG(j->first << " : " << j->second);
			}
			LOG("}");
		}
	}

	void LocalsTable::push()
	{
		m_Symbols.emplace_back();
	}

	void LocalsTable::pop()
	{
		m_Symbols.pop_back();
	}

}
