#pragma once

#include <memory>
#include <vector>
#include <string>

namespace apryx {

	class Statement;
	class Structure;
	class ApryxEnvironment;
	class ApryxClass;
	class Block;
	class Function;

	class ASTConverter {
		std::vector<std::string> m_ScopeStack;

	public:
		ASTConverter() {};
		~ASTConverter() {};

		void process(std::shared_ptr<Block> block, ApryxEnvironment &nmsp);


		void processSequencial(std::shared_ptr<Block> block);

	private:
		std::string getNamespace() const;

		void processOutline(std::shared_ptr<Function> structure, ApryxEnvironment &nmsp);
		void processFull(std::shared_ptr<Function> block, ApryxEnvironment &nmsp);

		void processOutline(std::shared_ptr<Structure> structure, ApryxClass &nmsp);
		void processFull(std::shared_ptr<Structure> block, ApryxClass &nmsp);
	};
}
