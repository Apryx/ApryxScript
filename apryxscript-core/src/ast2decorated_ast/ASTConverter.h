#pragma once

#include <memory>

namespace apryx {

	class Statement;
	class ApryxNamespace;

	class ASTConverter {
	public:
		ASTConverter() {};
		~ASTConverter() {};

		void processNamespace(std::shared_ptr<Block> block, ApryxNamespace &nmsp);
	};
}
