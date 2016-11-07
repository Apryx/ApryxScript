#pragma once

#include <memory>

namespace apryx {

	class Statement;
	class ApryxEnvironment;
	class Block;

	class ASTConverter {
		//std::

	public:
		ASTConverter() {};
		~ASTConverter() {};

		void process(std::shared_ptr<Block> block, ApryxEnvironment &nmsp);
	};
}
