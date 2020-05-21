#pragma once

#include <memory>

#include "ast/Statement.h";
#include "decorated_ast/ApryxFunction.h";
#include "decorated_ast/ApryxNamespace.h";

namespace apryx { 

	class Decorator{
	public:
		std::shared_ptr<ApryxNamespace> decorate(std::shared_ptr<CompilationUnit> unit);
	};

}