#pragma once

#include <memory>

namespace apryx {

	class Statement;
	class ApryxNamespace;

	class ASTConverter {
	public:
		ASTConverter() {};
		~ASTConverter() {};

		void process(std::shared_ptr<Statement> statement, ApryxNamespace &nmsp);
	};
}
