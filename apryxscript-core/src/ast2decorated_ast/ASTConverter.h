#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

#include <boost/optional.hpp>

#include "decorated_ast/Type.h"

namespace apryx {

	class Statement;
	class Structure;
	class ApryxEnvironment;
	class ApryxClass;
	class Block;
	class Function;
	class Expression;

	class LocalsTable {
		std::vector<std::map<std::string, Type>> m_Symbols;

	public:
		boost::optional<Type> getTypeOf(const std::string &name);
		bool setTypeOf(const std::string &name, const Type &type);

		boost::optional<Type> getTypeByName(const std::string &name);

		void dump();

		void push();
		void pop();
	};

	class ASTConverter {
		std::vector<std::string> m_ScopeStack;

	public:
		ASTConverter() {};
		~ASTConverter() {};

		void process(std::shared_ptr<Block> block, ApryxEnvironment &nmsp);


		void processSequencial(std::shared_ptr<Block> block, LocalsTable &table);
		void processSequencial(std::shared_ptr<Expression> expression, LocalsTable &table);

	private:
		std::string getNamespace() const;

		void processOutline(std::shared_ptr<Function> structure, ApryxEnvironment &nmsp);
		void processFull(std::shared_ptr<Function> block, ApryxEnvironment &nmsp);

		void processOutline(std::shared_ptr<Structure> structure, ApryxClass &nmsp);
		void processFull(std::shared_ptr<Structure> block, ApryxClass &nmsp);
	};
}
